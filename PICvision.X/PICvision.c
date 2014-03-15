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
#include "PICVision_banner.h"

void splash_screen(){
    int i,k,first,last,left;
    left=(HPIXELS-PIX_WIDTH)/16+1;
    last=0;
    while (last<(VPIXELS-PIX_HEIGHT)/2+PIX_HEIGHT){
        first=max(0,PIX_HEIGHT-last-1);
        for (i=0;i<PIX_HEIGHT-first;i++){
            for (k=0;k<ARRAY_WIDTH;k++){
                video_buffer[last-i][left+k]=PICVISION_BANNER[i][k];
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
    wait_n_frame(180);
}//f()


void PICvision_init(void) {
    HardwareConfig();
    timers_init(TICK_FREQ);
    video_init();
    sound_init(1000/TICK_FREQ);
    splash_screen();
}//f()


