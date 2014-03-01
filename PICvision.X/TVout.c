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
#define NSTC_FRAME_PER_SECOND 60
#define NTSC_LINE_PERIOD  (63.5*FCY/MHZ) // horizontal line period 63,5µsec
#define NTSC_FRONT_PORCH (1.5*FCY/MHZ)
#define NTSC_HPULSE (4.7*FCY/MHZ)
#define NTSC_FIRST_VISIBLE  30
#define NTSC_LAST_VISIBLE (NTSC_FIRST_VISIBLE+VPIXELS)
#define NTSC_VIDEO_DELAY (2*NTSC_HPULSE+40)

// PAL composite signal parameters
#define PAL_LINES_PER_FRAME (625/2)  // progressive scan
#define PAL_FRAME_PER_SECOND 50
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
#define F_RETRACE 8 // flag screen in retrace phase


static unsigned int frame_line_cntr=0; // count line in video frame
volatile static unsigned long frame_cntr=0; // number of frame since reset
volatile static unsigned int flags;


char video_buffer[VPIXELS][BYTES_PER_LINE];
int vsync, hsync, video_mode;

void ntsc_init(){
    PR2 = NTSC_LINE_PERIOD;
    OC1R= NTSC_HPULSE;
    OC1RS=NTSC_LINE_PERIOD;
    OC4R=NTSC_VIDEO_DELAY;
    OC4RS=NTSC_LINE_PERIOD-NTSC_FRONT_PORCH;
    hsync=NTSC_HPULSE;
    vsync=NTSC_LINE_PERIOD-NTSC_HPULSE;
    video_mode=NTSC_MODE;
}//f()

void pal_init(){
    PR2 = PAL_LINE_PERIOD;
    OC1R= PAL_HPULSE;
    OC1RS=PAL_LINE_PERIOD;
    OC4R=PAL_VIDEO_DELAY;
    OC4RS=PAL_LINE_PERIOD-PAL_FRONT_PORCH;
    hsync=PAL_HPULSE;
    vsync=PAL_LINE_PERIOD-PAL_HPULSE;
    video_mode=PAL_MODE;
}//f()

void  video_init(){ // initialisation sorties NTSC
    T2CON=0; // désactivation TIMER2
    if (P_VIDEO_MODE){
        ntsc_init();
    }else{
        pal_init();
    }
    // OC1 video sync
    OC1CON=5; // mode 5, timer 2
    //video sync interrupt setting.
    //IFS0bits.OC1IF=0;
    //IPC0bits.OC1IP=7;
    IPC4bits.CNIP=7;
    CNEN2bits.CN21IE=1;
    // timer 2 interrupt enabling
    IFS0bits.T2IF=0;
    IPC1bits.T2IP=7; // plus haute priorité
    IEC0bits.T2IE=1;
    // SPI1 configuration (pixel output)
    SPI1CON1=0;
    SPI1CON1bits.DISSCK=1;
    SPI1CON1bits.MSTEN=1;
    SPI1CON1bits.SPRE=5;
    SPI1CON1bits.PPRE=3;
    SPI1CON2=1;
    SPI1STATbits.SPIEN=1;
    T2CONbits.TON=1;
}//horz_sync_init()

void  wait_n_frame(unsigned n){
unsigned long f0;
    f0=frame_cntr+n;
    while (frame_cntr<f0);
}//f()




// video sync signal generation
void __attribute__((interrupt,no_auto_psv,shadow)) _T2Interrupt(void){
    frame_line_cntr++;
    switch (frame_line_cntr){
        case 1:
            OC1R=vsync;
            OC4CON=0;
            break;
        case 4:
            OC4CON=5;
            OC1R=hsync;
            break;
        case NTSC_FIRST_VISIBLE:
            if (video_mode==NTSC_MODE){
                IFS1bits.CNIF=0;
                IEC1bits.CNIE=1;
                flags &= ~F_RETRACE;
            }
            break;
        case NTSC_LAST_VISIBLE:
            if (video_mode==NTSC_MODE){
                IEC1bits.CNIE=0;
                flags |= F_RETRACE;
            }
            break;
        case PAL_FIRST_VISIBLE:
            if (video_mode==PAL_MODE){
                IFS1bits.CNIF=0;
                IEC1bits.CNIE=1;
                flags &= ~F_RETRACE;
            }
            break;
        case PAL_LAST_VISIBLE:
            if (video_mode==PAL_MODE){
                IEC1bits.CNIE=0;
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

//        default:
//            if (flags & F_RETRACE){
//                if (flags & F_CLEAR){
//                    memset((char*)video_buffer,0,sizeof(char)*VPIXELS*BYTES_PER_LINE);
//                    flags &= ~F_CLEAR;
//                    cursor_pos.y=0;
//                    cursor_pos.x=0;
//                } else if (flags & F_CLREOL){
//                    memset((char*)video_buffer[cursor_pos.y]+cursor_pos.x,
//                            0,sizeof(char)*(COLUMNS-cursor_pos.x));
//                    flags &= ~F_CLREOL;
//                }else if (flags & F_PCHAR){
//                    video_buffer[cursor_pos.y][cursor_pos.x]=pchar_queue[head]-32;
//                    cursor_forward();
//                    head++;
//                    head %= QUEUE_SIZE;
//                    if (head==tail){
//                        flags &= ~F_PCHAR;
//                    }
//                }//if
//            }//if
//            break;
    }//switch
    IFS0bits.T2IF=0;
}// _T2Interrupt()

void __attribute__((interrupt,no_auto_psv,shadow)) _CNInterrupt(void){
    int y,x;
    if (PORTBbits.RB9){
        if (video_mode==NTSC_MODE){
            y=(frame_line_cntr-NTSC_FIRST_VISIBLE);
        }else{
            y=(frame_line_cntr-PAL_FIRST_VISIBLE);
        }
        for (x=0;x<BYTES_PER_LINE;x++){
            while (SPI1STATbits.SPITBF);
            SPI1BUF=video_buffer[y][x];
        }//for
        while (SPI1STATbits.SPITBF);
        SPI1BUF=0;
    }
    IFS1bits.CNIF=0;
}// _CNInterrupt

