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
 * File:   TVout.h
 * Author: jacques Deschênes
 * Description:  NTSC/PAL signal generator
 *
 * Created on 25 février 2014, 16:28
 */

#ifndef TVOUT_H
#define	TVOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <PPS.h>
#include "hardwareProfile.h"
#include "font.h"

#define NTSC

#ifdef NTSC
#define VPERIOD 17
#else
#define VPERIOD 20
#endif

#define VPIXELS 216
#define HPIXELS 200
#define LINES (VPIXELS/8)
#define COLUMNS (HPIXELS/8)


void  video_init();
void  wait_n_frame(unsigned n);

void clear_screen();
void clear_eol();
void move_cursor(unsigned line, unsigned column);
unsigned  get_cursor();
void put_char(char c);
void print(const char *str);
void wait_while_printing();


#ifdef	__cplusplus
}
#endif

#endif	/* TVOUT_H */

