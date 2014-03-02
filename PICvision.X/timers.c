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
 *  NAME: timers.c
 *  DATE CREATED: 2014-02-21
 *  AUTHOR: Jacques Deschênes
 *  DESCRIPTION: create timers with callback. TIMER1 is used as a system timer that
 *               ticks at regular interval. The ISR of TIMER1 manage created timers.
 */

#include <stdlib.h>
#include "timers.h"

#define F_TMR_USED 1
#define F_TMR_HALTED 2
#define F_TMR_REPEAT 4
#define TMR_RUNNING 1


typedef struct timer_type{
    unsigned status;    // slot used,  timer halted
    unsigned delay;    // timer interval
    unsigned countdown;
    timer_handler_t *handler; // timer callback handler
}timer_t;

volatile static timer_t timers[MAX_TIMERS];
volatile static unsigned long ticks;

void timers_init(unsigned ticks_per_second){
    unsigned long quotient;
    unsigned prescale;
    int i;
    for (i=0;i<MAX_TIMERS;i++){
        timers[i].status=0;
        timers[i].handler=NULL;
    }//for
    ticks=0;

    SYSTICKTMR.TON=0;  // disable systick timer
    quotient = FCY/ticks_per_second;
    prescale=1;
    while (quotient>65535){
        quotient >>= 1;
        prescale <<= 1;
    }
    if (prescale==1){
        SYSTICKTMR.TCKPS=0;
        SYSTICKPR=quotient;
    }else if (prescale<=8){
        SYSTICKTMR.TCKPS=1;
        SYSTICKPR= FCY/ticks_per_second/8;
    }else if (prescale<=64){
        SYSTICKTMR.TCKPS=2;
        SYSTICKPR= FCY/ticks_per_second/64;
    }else{
        SYSTICKTMR.TCKPS=3;
        SYSTICKPR = FCY/ticks_per_second/256;
    }//if
    SYSTICKIF=0; // reset interrupt flag
    SYSTICKIE=1; // enable interrupt on systick timer
    SYSTICKTMR.TON = 1; // enable systick timer
}//f()

int create_timer(unsigned delay, unsigned repeat, timer_handler_t *handler){
    int i;
    if (!handler) return -1;
    for (i=0;i<MAX_TIMERS;i++){
        if (!(timers[i].status & F_TMR_USED)){
            timers[i].status = F_TMR_USED|F_TMR_HALTED;
            if (repeat==TIMER_REPEAT) {timers[i].status |= F_TMR_REPEAT;}
            timers[i].delay=delay;
            timers[i].countdown=delay;
            timers[i].handler=handler;
            return i;
        }//if
    }//for
    return -1;
}//f()

void stop_timer(int timer_id){
    if ((timer_id>=0) && (timer_id<MAX_TIMERS) &&
         (timers[timer_id].status & F_TMR_USED)){
        timers[timer_id].status |= F_TMR_HALTED;
    }//if
}//f()

void start_timer(int timer_id){
    if ((timer_id>=0) && (timer_id<MAX_TIMERS) &&
        (timers[timer_id].status & F_TMR_USED)){
            timers[timer_id].countdown=timers[timer_id].delay;
            timers[timer_id].status &= ~F_TMR_HALTED;
    }//if
}//f()

void update_timer(int timer_id, unsigned new_delay){
    if ((timer_id>=0)&&(timer_id<=MAX_TIMERS)&&timers[timer_id].status){
        timers[timer_id].delay=new_delay;
    }
}//f()

void destroy_timer(int timer_id){
    if ((timer_id<0)||(timer_id>=MAX_TIMERS)) return;
    timers[timer_id].status=0;
    timers[timer_id].handler=NULL;
}//f()

unsigned long sys_ticks(){
    return ticks;
}//f()

void __attribute__((interrupt,no_auto_psv)) _SYSTICK_ISR(void){
    int i;
    ticks++;
    for (i=0;i<MAX_TIMERS;i++){
        if (((timers[i].status&(F_TMR_USED|F_TMR_HALTED))==TMR_RUNNING)){
            if (--timers[i].countdown==0){
                timers[i].handler();
                if (timers[i].status & F_TMR_REPEAT) {
                    timers[i].countdown=timers[i].delay;
                }else{
                    timers[i].status |= F_TMR_HALTED;
                }
            }//if
        }
    }//for
    SYSTICKIF=0;
}// _SYSTICK_ISR()



