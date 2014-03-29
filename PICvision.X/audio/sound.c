/*
* Copyright 2014, Jacques Deschênes
* This file is part of PICvision.
*
*     PICvision is free software: you can redistribute it and/or modify
*     it under the terms of the GNU General Public License as published by
*     the Free Software Foundation, either version 3 of the License, or
*     (at your option) any later version.
*
*     PICvision is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*     GNU General Public License for more details.
*
*     You should have received a copy of the GNU General Public License
*     along with PICvision.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * File:   sound.c
 * Author: jacques Deschênes
 * Description:  sound generation using PWM D.A.C.
 * Created on 25 février 2014, 16:43
 */

#include <stdlib.h>
#include "sound.h"

#define F_TONE  1  // tone playing flag
#define F_TUNE  2  // flag tune playing
#define F_WHITE 4  // white noise generation

#define mTone_off() (AUDIOCON.OCM=0)
#define mTone_on()  (AUDIOCON.OCM=5)


static volatile unsigned char fSound=0; // boolean flags
static volatile int tmrId;  // duratio timer identifier
const unsigned  *  tones_list;  // list of tones and interval for playing tune
static int tick_msec=10; // tick interval in milliseconds, default 10msec.

void cb_tone(void){ // timer call back function
    mTone_off();
    fSound &= ~(F_TONE|F_WHITE);
}// f()

void sound_init(int tick_time){
    if (tick_time) tick_msec=tick_time;
    tmrId=create_timer(1,TIMER_SINGLE,(timer_handler_t *)cb_tone);
    AUDIOCON.OCTSEL=1; // select OCx timer
    AUDIOR=0;
    AUDIOTMR.TON=0;
    AUDIOTMR.TCKPS=1; // 1:8  // timer clock prescale divisor
}//f()

// play tone in background
void tone(unsigned freq, // frequency in hertz
          unsigned msec){ // duration in  milliseconds
    if (!(freq && msec))  return ;
    mTone_off(); 
    AUDIORS=FCY/16/freq; // determine tone duty cycle
    AUDIOTMR.TON=0;
    AUDIOPR=(FCY/8/freq)-1; // pwm period
    fSound |=F_TONE;
    mTone_on(); 
    AUDIOTMR.TON=1;
    update_timer(tmrId,msec/tick_msec);
    start_timer(tmrId);
} //tone();

// play tune in background
void tune(const unsigned *buffer){
    tones_list=(unsigned *)buffer;
    if (*tones_list && *(tones_list+1)){
        fSound |= F_TUNE;
        AUDIOIF=0;
        AUDIOIE=1;
        tone(*tones_list++,*tones_list++);
    }
}//tune()


void white_noise(unsigned msec){
    if (!fSound){
        AUDIOTMR.TON=0;
        AUDIOPR=(FCY/8/10000)-1; // pwm period
        AUDIOTMR.TON=0;
        AUDIOIF=0;
        AUDIOIE=1;
        AUDIOTMR.TON=1;
        update_timer(tmrId,msec/tick_msec);
        start_timer(tmrId);
    }
    fSound |= F_WHITE;
}// f()

void while_sound(){
    while (fSound);
}// f()

// interrupt at end of tone cycle
void __attribute__((interrupt, no_auto_psv))  _AUDIO_ISR(void){
   unsigned int f,d;
   if (fSound&F_WHITE){
       P_NOISE_OUT=rand()&1;
   }
   if (!fSound) {
       AUDIOIE=0;
       AUDIOTMR.TON=0;
   }else if (fSound==(fSound & F_TUNE)){
       f=*tones_list++;
       d=*tones_list++;
       if (d){
            if (f){
                tone(f,d);
            }else{
                update_timer(tmrId,d/tick_msec);
                start_timer(tmrId);
                fSound |= F_TONE;
                mTone_on();
            }
       }else{
           fSound=0;
           AUDIOIE=0;
           AUDIOTMR.TON=0;
       } // if
   }
   AUDIOIF=0;
}// _AUDIO_ISR


