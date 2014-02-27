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
 * File:   font.h
 * Author: Jacques Deschênes
 *
 * Created on 23 août 2013, 07:32
 */

#ifndef FONT_H
#define	FONT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CHAR_HEIGHT 8   // include empty line under character
#define CHAR_WIDTH 6    // include 2 empty dots on left side.
#define FONT_SIZE 98    // number of characters in table
    

extern const unsigned char font6x8[FONT_SIZE][CHAR_HEIGHT];




#ifdef	__cplusplus
}
#endif

#endif	/* FONT_H */

