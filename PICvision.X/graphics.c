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
 *      coordinates origin is screen top,left, x increase to right, y increase to bottom
 * Created on 28 février 2014, 13:07
 */

#include <stdlib.h>
#include "graphics.h"

// draw a dot

void plot(int x, int y, int color){
    int h,ofs;
    if ((y>=VPIXELS)||(x>=HPIXELS)) return; // bound check
    h= x/8;
    ofs = 7 - x%8;
    if (color==WHITE)
        video_buffer[y][h]|= (1<<ofs);
    else
        video_buffer[y][h]&= ~(1<<ofs);
} // plot()

// dessine une droite en utilisant l'algorithme de Bresenham
void line(int x1, int y1, int x2, int y2, int color){
    int deltax,deltay;
    plot(x1,y1,color);
    if (y1==y2){// cas particulier ligne horizontale
        deltax= x1<x2?1:-1;
        while (x1!=x2){
            x1 += deltax;
            plot(x1,y1,color);
        }
    }else if (x1==x2){ // cas particulier ligne verticale
        deltay= y1<y2?1:-1;
        while (y1!=y2){
            y1+=deltay;
            plot(x1,y1,color);
        }
    }else{
        int sx,sy,err,e2;
        deltax=abs(x2-x1);
        deltay=abs(y2-y1);
        sx = x1<x2?1:-1;
        sy = y1<y2?1:-1;
        err=deltax-deltay;
        while (!((x1==x2) && (y1==y2))){
            e2=err<<1;
            if (e2>-deltay){
               err -= deltay;
               x1 += sx;
            }else if (e2<deltax){
                err +=deltax;
                y1 += sy;
            }
            plot(x1,y1,color);
        }
    }
} // line()

void rectangle(int x1, int y1, int x2, int y2, int color){
    line(x1,y1,x1,y2,color);
    line(x2,y1,x2,y2,color);
    line(x1,y1,x2,y1,color);
    line(x1,y2,x2,y2,color);
}//rectangle()

/*  algorthme mid-point
 * REF: http://www.hhhprogram.com/2013/05/draw-elipse-midpoint-elipse-algorithm.html
 */
void ellipse (int xc, int yc, long rx, long ry, int color){
          long  x=0,y=ry;
          long  p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4);
          while((2*x*ry*ry)<(2*y*rx*rx)){
               plot(xc+x,yc-y,color);
               plot(xc-x,yc+y,color);
               plot(xc+x,yc+y,color);
               plot(xc-x,yc-y,color);
               if(p<0){
                   x=x+1;
                   p=p+(2*ry*ry*x)+(ry*ry);
               }else {
                   x=x+1;
                   y=y-1;
                   p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
               }
          }
          p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;
          while(y>=0){
               plot(xc+x,yc-y,color);
               plot(xc-x,yc+y,color);
               plot(xc+x,yc+y,color);
               plot(xc-x,yc-y,color);
               if(p>0){
                   y=y-1;
                   p=p-(2*rx*rx*y)+(rx*rx);
               }else{
                   y=y-1;
                   x=x+1;
                   p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
               }
          }
}//ellipse()

/*
 * points[]={x1,y1,x2,y2,x3,y3,...}
 * vertices est le nombre de points
 */
void polygon(int points[], int vertices, int color){
    int i;
    for(i=0;i<(2*vertices-2);i+=2){
        line(points[i],points[i+1],points[i+2],points[i+3],color);
    }
    line(points[0],points[1],points[i],points[i+1],color);
}//polygon()


