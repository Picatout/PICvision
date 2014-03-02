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


#include "sound.h"



volatile unsigned char fSound=0; // indicateurs booléins
volatile int tmrId;
volatile unsigned int *tones_list;
int tick_msec;
void cbSoundOff(void){ // timer call back function
    mTone_off();
    fSound &= ~TONE_ON;
}// f()

void sound_init(int tick_time){
    tick_msec=tick_time;
    tmrId=create_timer(1,TIMER_SINGLE,(timer_handler_t *)cbSoundOff);
}//f()

void tone(unsigned freq, // fréquency in hertz
          unsigned msec){ // duration in  milliseconds
    //
    mTone_off(); // pwm continuous mode
    AUDIOCON.OCTSEL=1; // select OCx timer
    AUDIORS=0;
    AUDIOR=FCY/16/freq;
    AUDIOTMR.TON=0;
    AUDIOTMR.TCKPS=1; // 1:8
    AUDIOPR=(FCY/8/freq)-1; // pwm ratio 50%
    fSound |=TONE_ON;
    mTone_on();
    AUDIOTMR.TON=1;
    update_timer(tmrId,msec/tick_msec);
    start_timer(tmrId);
} //tone();

// joue une mélodie en arrière plan
void tune(const unsigned *buffer){
    tones_list=(unsigned *)buffer;
    if (*tones_list && *(tones_list+1)){
        fSound |= PLAY_TUNE;
        AUDIOIF=0;
        AUDIOIE=1;
        tone(*tones_list++,*tones_list++);
    }
}//tune()



void __attribute__((interrupt, no_auto_psv))  _AUDIO_ISR(void){
    unsigned int f,d;
       if (fSound==PLAY_TUNE){
           f=*tones_list++;
           d=*tones_list++;
           if (d){
                if (f){
                    tone(f,d);
                }else{
                    update_timer(tmrId,*tones_list/tick_msec);
                    start_timer(tmrId);
                    fSound |= TONE_ON;
                }
           }else{
               fSound=0;
               AUDIOIE=0;
               AUDIOTMR.TON=0;
           } // if
       }//if
}// _AUDIO_ISR


