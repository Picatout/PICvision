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

typedef enum BMP_OP_ENUM {BMP_COPY,BMP_OR,BMP_AND,BMP_XOR} bmp_op_t;

/* void plot(int x, int y, int color)
 * Description: draw a dot on screen
 * parameters:
 *    - x   horizontal coordinate in pixels
 *    - y   vertical coordinateur in pixels
 *    - color   one of BLACK, WHITE, INVERT
 */
void plot(int x, int y, int color);

/*void line(int x1, int y1, int x2, int y2, int color)
 *  Description:  draw a line on screen
 *  parameters:
 *      - x1  line end first horizontal coordinate in pixels
 *      - y1  line end first vertical coordinate in pixels
 *      - x2  line end second horizontal coordinate in pixels
 *      - y2  line end second vertical coordinate in pixels
 *    - color   one of BLACK, WHITE, INVERT
 */
void line(int x1, int y1, int x2, int y2, int color);

/*void rectangle(int x1, int y1, int x2, int y2, int color)
 *  Description: draw a rectangle on screen
 *  parameters:
 *      - x1  first corner horizontal coordinate in pixels
 *      - y1  first corner vertical coordinate in pixels
 *      - x2  second diagonal corner horizontal coordinate in pixels
 *      - y2  second diagonal corner vertical coordinate in pixels
 *      - color one of BLACK, WHITE, INVERT
 */
void rectangle(int x1, int y1, int x2, int y2, int color);

/*void ellipse (int xc, int yc, long rx, long ry, int color)
 *  Description: Draw an ellipse on screen
 *  parameters:
 *      - xc    ellipse center horizontal coordinate in pixels
 *      - yc    ellipse center vertical coordinate in pixels
 *      - rx    horizontal axe length in pixels
 *      - ry    vertical axe length ni pixels
 *      - color one of BLACK, WHITE, INVERT
 */
void ellipse (int xc, int yc, long rx, long ry, int color);

/* void polygon(int points[],int vertices, int color)
 * Description: draw a polygon on screen
 * parameters:
 *      - points[] array of vertices points
 *      - vertices number of vertices in array
 *      - color one of BLACK, WHITE, INVERT
 */
void polygon(int points[],int vertices, int color);


/* void box(int left, int top, int width, int height, int color)
 * Description: bit operations on rectangular area in video_buffer
 *
 * parameters:
 *     - left    x coordinate of top-left   corner
 *     - top     y coordinate of top-left   corner
 *     - width   horizontal size of rectangle in pixels
 *     - height  vertical size of rectangle in pixels
 *     - color   one of BLACK, WHITE, INVERT
 */
void box(int left, int top, int width, int height,int color);


/* bitmap(int left, int top, int width, int height, bmpr1op_t op, char* bmp)
 * Description: bit logical operations between rectangular area in video_buffer and
 *              bitmap array
 * arguments:
 *     - left    x coordinate of top-left   corner
 *     - top     y coordinate of top-left   corner
 *     - width   horizontal size of rectangle in pixels
 *     - height  vertical size of rectangle in pixels
 *     - op      operation to be executed
 *     - bmp     pointer to bitmap array used in operation
 *               bitmap with width less than 8 bits must have
 *               their bits align left and other bits to zero.
 */
void bitmap(int left, int top, int width, int height, bmp_op_t op, const unsigned char* bmp);


#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */

