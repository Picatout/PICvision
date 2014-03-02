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
 * File:   hardwareProfile.h
 * Author: jacques Deschênes
 * Description:  try to centralize  hardware specific.
 * Created on 25 février 2014, 16:21
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include <PPS.h>


#define MHZ 1000000UL
#define FOSC (32*MHZ)  // 8Mhz crystal x 4 (internal PLL)
#define FCY  (FOSC/2)    // core cycle frequency
#define TICK_FREQ 100  // system ticks per second

// video mode input pin configuration bits
#define P_VIDEO_MODE PORTBbits.RB12 // video mode detect input pin
#define P_VIDEO_MODE_TRIS TRISBbits.TRISB12 // video mode input TRIS SFR bit
#define VIDMODE_ANDIS AD1PCFGbits.PCFG12 // disable analog input on video mode input pin
// audio out SFR and bits
#define AUDIOCON    OC2CONbits   // audio OCxCON  SFR bits
#define AUDIOR      OC2R         // audio OCxR  SFR
#define AUDIORS     OC2RS       //  audio OCxRS SFR
#define AUDIOTMR    T3CONbits   // audio TxCON SFR  bits
#define AUDIOPR     PR3         // audio PRx  SFR
#define P_AUDIO_OUT_TRIS TRISBbits.TRISB8 // audio output TRIS SFR bit
#define AUDIOIP     IPC2bits.T3IP // audio output timer interrupt priority
#define AUDIOIF     IFS0bits.T3IF // audio timer interrupt flag bit
#define AUDIOIE     IEC0bits.T3IE // audio timer interrupt enable bit
#define _AUDIO_ISR  _T3Interrupt  // audio timer interrupt

// video out SFR and bits
#define P_PIXEL_OUT_TRIS TRISBbits.TRISB5 // pixel output TRIS SFR bit
#define VDLYCON     OC4CONbits   // video delay OCxCON SFR bits
#define VDLYR       OC4R        // video delay OCxR SFR
#define VDLYRS      OC4RS       // video delay OCxRS SFR
#define PIXDLY_INP  PORTBbits.RB9 // video delay input pin change notification
#define P_PIXDLY_IN_TRIS  TRISBbits.TRISB9 // video delay input TRIS SFR bit
#define PIXCON1     SPI1CON1bits // pixels output (SPI) SPIxCON1 SFR bits
#define PIXCON2     SPI1CON2bits // pixels output (SPI) SPIxCON2 SFR bits
#define PIXSTAT     SPI1STATbits // pixels output (SPI) SPIxSTAT SFR bits
#define PIXBUF      SPI1BUF      // pixels output SPI buffer SFR
#define VDLYIF      IFS1bits.CNIF // video pixels out interrupt flag bit
#define VDLYIE      IEC1bits.CNIE // video pixels out interrupt enable bit
#define P_VDLY_OUT_TRIS TRISBbits.TRISB6 // video delay out TRIS SFR bit
#define PIXIE       CNEN2bits.CN21IE // pin change interrupt enable bit
#define VIDTMR      T2CONbits    // video out TxCON SFR bits
#define VIDPR       PR2          // video timer PRx SFR
#define PIXIP       IPC4bits.CNIP // video pixel output interrupt priority
// video sync SFR and bits
#define VSYNCCON    OC1CONbits   // video sync OCxCON SFR bits
#define VSYNCR      OC1R        // video sync OCxR SFR
#define VSYNCRS     OC1RS       // video sync OCxRS SFR
#define P_VSYNC_OUT_TRIS TRISBbits.TRISB7 // video sync output TRIS SFR bit
#define VSYNCIF     IFS0bits.T2IF // video sync interrupt flag  bit
#define VSYNCIE     IEC0bits.T2IE // video sync interrupt enable bit
#define VSYNCIP     IPC1bits.T2IP // video sync out interrupt priority
// interrupt vectors
#define _VSYNC_ISR _T2Interrupt  // video sync interrupt vector
#define _VIDEO_OUT_ISR _CNInterrupt   // video out interrupt vector
#define _AUDIO_ISR _T3Interrupt  // audio outup interrupt vector
// system tick timer
#define SYSTICKTMR  T1CONbits  // system tick timer config SFR bits
#define SYSTICKPR   PR1        // system tick timer PRx SFR
#define SYSTICKIP   IPC0bits.T1IP // system tick timer interrupt priority
#define SYSTICKIF   IFS0bits.T1IF // system tick timer interrupt flag bit
#define SYSTICKIE   IEC0bits.T1IE // system tick timer interrupt enable bit
#define _SYSTICK_ISR _T1Interrupt // system tick timer interrupt

// interface functons
void HardwareConfig();

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_H */

