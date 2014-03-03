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
 * File:   graphics.h
 * Author: jacques Deschênes
 * Description: Draw geometrics figures.
 * Created on 28 février 2014, 13:07
 */

#ifndef GRAPHICS_H
#define	GRAPHICS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "TVout.h"

#define BLACK 0
#define WHITE 1
#define INVERT 2


void plot(int x, int y, int color);
void line(int x1, int y1, int x2, int y2, int color);
void rectangle(int x1, int y1, int x2, int y2, int color);
void ellipse (int xc, int yc, long rx, long ry, int color);
void polygon(int points[],int vertices, int color);


#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */

