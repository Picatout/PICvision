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
#include "../Hardware/hardwareProfile.h"




#define VPIXELS 216
#define HPIXELS 216
#define BYTES_PER_LINE (HPIXELS/8)

#define VIDEO_OFF 1
#define VIDEO_ON  0

typedef union coord_type{
    unsigned int yx;
    struct{
        unsigned char y;
        unsigned char x;
    };
}coord_t;


extern unsigned char __attribute__((aligned(2))) video_buffer[VPIXELS][BYTES_PER_LINE];
extern int video_mode;
extern unsigned frames_per_second;

void  video_init();
void  wait_n_frame(unsigned n);
void  blank_out();
int  get_frame_count();

#ifdef	__cplusplus
}
#endif

#endif	/* TVOUT_H */

