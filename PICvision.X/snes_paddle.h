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
 * File:   snes_paddle.h
 * Author: jacques Deschênes
 * Description:  SNES gemepad interface
 * Created on 25 février 2014, 16:41
 */

#ifndef SNES_PADDLE_H
#define	SNES_PADDLE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "hardwareProfile.h"

#define PADDLE1  1
#define PADDLE2  2

// paddle buttons
#define SNES_B       0x01
#define SNES_Y       0x02
#define SNES_SELECT  0x04
#define SNES_START   0x08
#define SNES_UP      0x10
#define SNES_DOWN    0x20
#define SNES_LEFT    0x40
#define SNES_RIGHT   0x80
#define SNES_A       0x100
#define SNES_X       0x200
#define SNES_L       0x400
#define SNES_R       0x800


unsigned read_paddle(int paddleId);


#ifdef	__cplusplus
}
#endif

#endif	/* SNES_PADDLE_H */

