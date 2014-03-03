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
 * Created on 1 march 2014
 */

#include "hardwareProfile.h"

void HardwareConfig(){
    // peripheral to pin association.
    PPSUnLock;
    PPSOutput(PPS_RP5,PPS_SDO1);   // video pixels output
    PPSOutput(PPS_RP6,PPS_OC4);  // video delay output
    PPSOutput(PPS_RP7,PPS_OC1);  // video sync output
    PPSOutput(PPS_RP8,PPS_OC2);  // audio output
    PPSLock;
    // pins data direction
    P_PIXEL_OUT_TRIS=0;     // video pixels output
    P_VDLY_OUT_TRIS=0;     // video delay output
    P_VSYNC_OUT_TRIS=0;     // video sync output
    P_AUDIO_OUT_TRIS=0;     // audio output
    P_NOISE_OUT_TRIS=0;     /// white noise output
    P_PIXDLY_IN_TRIS=1;     //input video pixels delay
    P_VIDEO_MODE_TRIS=1;    //input NTSC/PAL select input
    VIDMODE_ANDIS=1;   // disable ADC  on NTSC/PAL select input.
    // interrupts priorities
    VSYNCIP=7;  // timer interrupt used for video output must have highest priority
    PIXIP=7;  // change notification interrupt used for video pixels must have highest priority
    AUDIOIP=3; // audio output timer interrupt priority
    SYSTICKIP=2; // system ticks timer interrupt priority

}//f()

