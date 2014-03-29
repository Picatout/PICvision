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

#include "PICvision.h"
#include "PICvision_banner.h"
#include "games/snake/snake.h"

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


void splash_screen(){
    int i,k,first,last,left;
    left=(HPIXELS-PIX_WIDTH)/16+1;
    last=0;
    while (last<(VPIXELS-PIX_HEIGHT)/2+PIX_HEIGHT){
        first=max(0,PIX_HEIGHT-last-1);
        for (i=0;i<PIX_HEIGHT-first;i++){
            for (k=0;k<ARRAY_WIDTH;k++){
                video_buffer[last-i][left+k]=PICVISION_BANNER[PIX_HEIGHT-1-i][k];
            }//for
        }//for
        if (last-i>0){
            for (k=0;k<ARRAY_WIDTH;k++){
                video_buffer[last-i-1][left+k]=0;
            }//for
        }//if
        wait_n_frame(1);
        last++;
    }//while
    set_curpos(left,last/8+2);
    print("Copyright 2014, Jacques Deschenes");
    wait_n_frame(120);
}//f()


void PICvision_init(void) {
    HardwareConfig();
    timers_init(TICK_FREQ);
    video_init();
    sound_init(1000/TICK_FREQ);
    splash_screen();
}//f()


int main(void){
   menu_t *games_list;
   int selected;
   PICvision_init();
   games_list=create_menu("SELECT GAME");
   add_menu_item("snake",1,games_list);
   add_menu_item("game 2",2,games_list);
   add_menu_item("game 3",3,games_list);
   add_menu_item("etc...",4,games_list);
   while(1){
       clear_screen();
       selected=run_menu(games_list,10,(27-5)/2,PADDLE1);
       selected=1;
       switch(selected){
           case 1:
               snake_game();
               break;
           case 2:
               set_curpos(0,0);
               print("game 2");
               wait_n_frame(60);
               break;
           case 3:
               set_curpos(0,0);
               print("game 3");
               wait_n_frame(60);
               break;
           case 4:
               set_curpos(0,0);
               print("autre jeux");
               wait_n_frame(60);
               break;
       }//switch
   }//while
   return 0;
}//main()

