/*
* Copyright 2014, Jacques Desch�nes
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
 * File:   sound.h
 * Author: jacques Desch�nes
 * Description:  sound generation using PWM D.A.C.
 * Created on 25 f�vrier 2014, 16:43
 */

#ifndef SOUND_H
#define	SOUND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "hardwareProfile.h"
#include "timers.h"


#define TONE_ON  1
#define PLAY_TUNE 2

#define mTone_off() (AUDIOCON.OCM=0)
#define mTone_on()  (AUDIOCON.OCM=5)

extern volatile unsigned char fSound; // boolean flags
extern volatile unsigned int duration;

void sound_init();
void tone(unsigned freq, unsigned duration);
void tune(const unsigned  *buffer);




#ifdef	__cplusplus
}
#endif

#endif	/* SOUND_H */

