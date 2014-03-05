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
 * File:   PICvision.c
 * Author: jacques Deschênes
 * Description:  a simple video game console on PIC24FJ64GA002 MCU
 *               inspiration come from HACKvision console.
 *               REF: https://nootropicdesign.com/hackvision/
 *     - display  NTSC/PAL  monochrome
 *     - resolution  216x216 pixels
 *     - controls: 2 SNES paddle  (cheap and easy to find.)
 *     - audio out:  monophonic  PWM DAC  or square wave tones
 *
 * Created on 25 février 2014, 16:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "hardwareProfile.h"
#include "TVout.h"
#include "text_console.h"
#include "graphics.h"
#include "sound.h"
#include "snes_paddle.h"

// PIC24FJ64GA002 Configuration Bit Settings
// CONFIG2
#pragma config POSCMOD = HS             // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON             // IOLOCK Protection (Once IOLOCK is set, cannot be changed)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config SOSCSEL = LPSOSC         // Sec Oscillator Select (Low Power Secondary Oscillator (LPSOSC))
#pragma config WUTSEL = FST             // Wake-up timer Select (Fast Wake-up Timer)
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)


const char msg[]="bouncing ring demo.";
const unsigned scale[]={523,500,587,500,659,500,698,500,784,500,880,500,988,500,1046,500,0,0};
int main(void) {
    int y,x,dx,dy, rebound=0;
    unsigned p;
    HardwareConfig();
    timers_init(TICK_FREQ);
    video_init();
    sound_init(10);
    while (1){
        wait_n_frame(2);
        p=read_paddle(PADDLE1);
        if (p){
            print_hex(p,3);
            crlf();
        }
    }
    tune(scale);
    print(msg);
    rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
    y=108;
    x=100;
    ellipse(x,y,10,10,WHITE);
    dx=0;
    dy=0;
    srand(time(0));
    while (!(dx&&dy)){
        dx=rand()%4-1;
        dy=rand()%4-1;
    }
    while (1){
        wait_n_frame(1);
        ellipse(x,y,10,10,BLACK);
        x +=dx;
        if (x<=10){
            x=11;
            dx=-dx;
            rebound=1;
        }else if (x>=HPIXELS-12){
            x=HPIXELS-12;
            dx=-dx;
            rebound=1;
        }
        y +=dy;
        if (y<=CHAR_HEIGHT+10){
            y=CHAR_HEIGHT+11;
            dy = -dy;
            rebound=1;
        }else if (y>=VPIXELS-12){
            y=VPIXELS-12;
            dy=-dy;
            rebound=1;
        }
        if (rebound){
            white_noise(20);
            rebound=0;
        }
        ellipse(x,y,10,10,WHITE);

    }//while
    return (EXIT_SUCCESS);
}//main()


