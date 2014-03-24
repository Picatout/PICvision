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
 * File:   sound.h
 * Author: jacques Deschênes
 * Description:  sound generation using PWM D.A.C.
 * Created on 25 février 2014, 16:43
 */

#ifndef SOUND_H
#define	SOUND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../Hardware/hardwareProfile.h"
#include "../system/timers.h"




void sound_init(int tick_time);
void tone(unsigned freq, unsigned duration);
void tune(const unsigned  *buffer);
void white_noise(unsigned msec);
void while_sound();



#ifdef	__cplusplus
}
#endif

#endif	/* SOUND_H */

