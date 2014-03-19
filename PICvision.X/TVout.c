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
 * File:   TVout.c
 * Author: jacques Deschênes
 * Description:  NTSC/PAL signal generator
 * NTSC REF: http://www.ntsc-tv.com/ntsc-index-02.htm
 * NTSC/PAL/SECAM REF: http://www.videointerchange.com/pal_secam_conversions.htm
 * Created on 25 février 2014, 16:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TVout.h"

// NTSC composite signal parameters
#define NTSC_LINES_PER_FRAME (525/2) // progressive scan
#define NTSC_FRAMES_PER_SECOND 60
#define NTSC_LINE_PERIOD  (63.5*FCY/MHZ) // horizontal line period 63,5µsec
#define NTSC_FRONT_PORCH (1.5*FCY/MHZ)
#define NTSC_HPULSE (4.7*FCY/MHZ)
#define NTSC_FIRST_VISIBLE  30
#define NTSC_LAST_VISIBLE (NTSC_FIRST_VISIBLE+VPIXELS)
#define NTSC_VIDEO_DELAY (2*NTSC_HPULSE+40)

// PAL composite signal parameters
#define PAL_LINES_PER_FRAME (625/2)  // progressive scan
#define PAL_FRAMES_PER_SECOND 50
#define PAL_LINE_PERIOD (64*FCY/MHZ)  // horizontal line period 64µsec
#define PAL_FRONT_PORCH (1.6*FCY/MHZ)
#define PAL_HPULSE (4.7*FCY/MHZ)
#define PAL_FIRST_VISIBLE  55
#define PAL_LAST_VISIBLE (PAL_FIRST_VISIBLE+VPIXELS)
#define PAL_VIDEO_DELAY (2*PAL_HPULSE+45)

#define NTSC_MODE 0
#define PAL_MODE 1

#define F_PCHAR 1    // flag put_char() pending
#define F_CLEAR 2    // flag clear_screen() pending
#define F_CLREOL 4   // flag clear to end of line
#define F_RETRACE 8  // flag screen in retrace phase
#define F_BLANK 16   // flag keep screen blank

unsigned frames_per_second;
static unsigned int frame_line_cntr=0; // count line in video frame
volatile static unsigned long frame_cntr=0; // number of frame since reset
volatile static unsigned int flags;


char video_buffer[VPIXELS][BYTES_PER_LINE];
int vsync, hsync, video_mode;

void ntsc_init(){
    VIDPR = NTSC_LINE_PERIOD;  // video timer PRx SFR
    VSYNCR= NTSC_HPULSE;       // video OCxR  SFR
    VSYNCRS=NTSC_LINE_PERIOD;  // video OCxRS SFR
    VDLYR=NTSC_VIDEO_DELAY;     // video delay OCxR SFR
    VDLYRS=NTSC_LINE_PERIOD-NTSC_FRONT_PORCH;  // video delay OCxRS SFR
    hsync=NTSC_HPULSE;
    vsync=NTSC_LINE_PERIOD-NTSC_HPULSE;
    video_mode=NTSC_MODE;
    frames_per_second=NTSC_FRAMES_PER_SECOND;
}//f()

void pal_init(){
    VIDPR = PAL_LINE_PERIOD;
    VSYNCR= PAL_HPULSE;
    VSYNCRS=PAL_LINE_PERIOD;
    VDLYR=PAL_VIDEO_DELAY;
    VDLYRS=PAL_LINE_PERIOD-PAL_FRONT_PORCH;
    hsync=PAL_HPULSE;
    vsync=PAL_LINE_PERIOD-PAL_HPULSE;
    video_mode=PAL_MODE;
    frames_per_second=PAL_FRAMES_PER_SECOND;
}//f()

void  video_init(){ // initialisation sorties NTSC
    VIDTMR.TON=0; // désactivation TIMER2
    if (P_VIDEO_MODE){
        ntsc_init();
    }else{
        pal_init();
    }
    //  video sync OC mode
    VSYNCCON.OCM=5; // mode 5, timer 2
    //video delay change notification interrupt enable on that pin.
    PIXIE=1;
    // video sync interrupt enabling
    VSYNCIF=0;
    VSYNCIE=1;
    // SPIx configuration (pixels output)
    PIXCON1.DISSCK=1;
    PIXCON1.MSTEN=1;
    PIXCON1.SPRE=5;
    PIXCON1.PPRE=3;
    PIXCON2.SPIBEN=1;  // enhanced buffer mode
    PIXSTAT.SPIEN=1;
    VIDTMR.TON=1;
}//horz_sync_init()

void  wait_n_frame(unsigned n){
unsigned long f0;
    f0=frame_cntr+n;
    while (frame_cntr<f0);
}//f()

void  blank_out(unsigned state){
    if (!state){
        flags &= ~F_BLANK;
    }else{
        flags |=F_BLANK;
    }
}//f()


// video sync signal generation
void __attribute__((interrupt,no_auto_psv,shadow)) _VSYNC_ISR(void){
    frame_line_cntr++;
    switch (frame_line_cntr){
        case 1:
            VSYNCR=vsync;
            VDLYCONR &=0xF8;
            break;
        case 4:
            VDLYCONR |=5;
            VSYNCR=hsync;
            break;
        case NTSC_FIRST_VISIBLE:
            if (video_mode==NTSC_MODE && !(flags&F_BLANK)){
                VDLYIF=0;
                VDLYIE=1;
                flags &= ~F_RETRACE;
            }
            break;
        case NTSC_LAST_VISIBLE:
            if (video_mode==NTSC_MODE){
                VDLYIE=0;
                flags |= F_RETRACE;
            }
            break;
        case PAL_FIRST_VISIBLE:
            if (video_mode==PAL_MODE && !(flags&F_BLANK)){
                VDLYIF=0;
                VDLYIE=1;
                flags &= ~F_RETRACE;
            }
            break;
        case PAL_LAST_VISIBLE:
            if (video_mode==PAL_MODE){
                VDLYIE=0;
                flags |= F_RETRACE;
            }
            break;
        case NTSC_LINES_PER_FRAME+1:
            if (video_mode==NTSC_MODE){
                frame_line_cntr=0;
                frame_cntr++;
            }
            break;
        case PAL_LINES_PER_FRAME+1:
            if (video_mode==PAL_MODE){
                frame_line_cntr=0;
                frame_cntr++;
            }
            break;
    }//switch
    VSYNCIF=0;
}// _VSYNC_ISR()

void __attribute__((interrupt,no_auto_psv,shadow)) _VIDEO_OUT_ISR(void){
    int y,x;
    if (PIXDLY_INP){
        if (video_mode==NTSC_MODE){
            y=(frame_line_cntr-NTSC_FIRST_VISIBLE);
        }else{
            y=(frame_line_cntr-PAL_FIRST_VISIBLE);
        }
        for (x=0;x<BYTES_PER_LINE;x++){
            while (PIXSTAT.SPITBF);
            PIXBUF=video_buffer[y][x];
        }//for
        while (PIXSTAT.SPITBF);
        PIXBUF=0;
    }
    VDLYIF=0;
}// _VIDEO_OUT_ISR

