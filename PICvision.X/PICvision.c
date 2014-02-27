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
 *               inpiration come from HACKvision console.
 *               REF: https://nootropicdesign.com/hackvision/
 *     - display  NTSC/PAL  monochrome
 *     - resolution  200x216 pixels
 *     - controls: 2 SNES paddle  (cheap and easy to find.)
 *     - audio out:  monophonic  PWM DAC
 *
 * Created on 25 février 2014, 16:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <PPS.h>

#include "hardwareProfile.h"
#include "TVout.h"

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

void HardwareConfig(){
    PPSUnLock;
    PPSOutput(PPS_RP5,PPS_OC2);   // audio output
    PPSOutput(PPS_RP6,PPS_OC1);   // video sync
    PPSOutput(PPS_RP7,PPS_SDO1);  // video pixels
    PPSOutput(PPS_RP10,PPS_OC3);  // video pedestal (black level)
    TRISBbits.TRISB5=0;
    TRISBbits.TRISB6=0;
    TRISBbits.TRISB7=0;
    TRISBbits.TRISB10=0;
    TRISBbits.TRISB11=1;
    PPSLock;
}//f()

const char msg[]="hello world!";
const char numbers[]=" 234567890123456789012|";

int main(void) {
    int y;
    HardwareConfig();
    video_init();
    for (y=0;y<LINES;y++){
        move_cursor(y,0);
        put_char(96+' ');
        wait_n_frame(1);
        move_cursor(y,COLUMNS-1);
        put_char(97+' ');
        wait_n_frame(1);
    }
    while (1){
        
    }//while
    return (EXIT_SUCCESS);
}//main()


