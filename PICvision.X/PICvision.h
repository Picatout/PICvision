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
 * File:   PICvision.h
 * Author: jacques Deschênes
 * Description:  a simple video game console on PIC24FJ64GA002 MCU
 *               inspiration come from HACKvision console.
 *               REF: https://nootropicdesign.com/hackvision/
 *     - display  NTSC/PAL  monochrome
 *     - resolution  216x216 pixels
 *     - controls: 2 SNES paddle  (cheap and easy to find.)
 *     - audio out:  monophonic  PWM DAC  or square wave tones
 *
 * Created on 5 mars 2014, 16:05
 */

#ifndef PICVISION_H
#define	PICVISION_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include "hardwareProfile.h"
#include "TVout.h"
#include "text_console.h"
#include "graphics.h"
#include "sound.h"
#include "snes_paddle.h"

void PICvision_init(void);



#ifdef	__cplusplus
}
#endif

#endif	/* PICVISION_H */

