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
    unsigned char mask;
    if ((y>=VPIXELS)||(x>=HPIXELS)) return; // bound check
    h= x/8;
    ofs = 7 - x%8;
    mask = 1<<ofs;
    switch (color){
        case BLACK:
            video_buffer[y][h]&= ~mask;
            break;
        case WHITE:
            video_buffer[y][h]|= mask;
            break;
        case INVERT:
            video_buffer[y][h] ^= mask;
            break;
    }
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


void box(int left, int top, int width, int height,int color){
    int y, x,idx,mwidth,bitsleft;
    unsigned char mask;
    for (y=top;y<top+height;y++){
        x=left;
        bitsleft=width;
        while (bitsleft){
            idx=x/8;
            if (x%8==0){
                mask=0xff;
                mwidth=8;
            }else{
                mask=0xff>>(x%8);
                mwidth=8-x%8;
            }
            if (bitsleft<mwidth){
                mask &= 0xff<<(mwidth-bitsleft);
                mwidth=bitsleft;
            }
            switch(color){
                case BLACK:
                    video_buffer[y][idx] &= ~mask;
                    break;
                case WHITE:
                    video_buffer[y][idx] |= mask;
                    break;
                case INVERT:
                    video_buffer[y][idx] ^= mask;
                    break;
            }//switch
            x += mwidth;
            bitsleft -= mwidth;
        }//while
    }//for
}//f()



void bitmap(int left, int top, int width, int height, bmp_op_t op, const unsigned char* bmp){
    int x,y, xbmp,mwidth,idx, bitsleft,ybmp_inc;
    unsigned char  mask, bmpbits, *ybmp;

    ybmp_inc=width/8;
    if (width%8) ybmp_inc++;
    ybmp=bmp;
    //remainder=0;
    for (y=top;y<top+height;y++){
        x=left;
        xbmp=0;
        bitsleft=width;
        while (bitsleft){
            idx=x/8;
            if (x%8==0){
                mask=0xff;
                mwidth=8;
            }else{
                mask=0xff>>(x%8);
                mwidth=8-x%8;
            }
            if (bitsleft<mwidth){
                mask &= 0xff<<(mwidth-bitsleft);
                mwidth=bitsleft;
            }
            bmpbits = (*(ybmp+xbmp/8))<<(xbmp%8);
            if (xbmp%8){
                bmpbits |= (*(ybmp+xbmp/8+1))>>(8-xbmp%8);
            }
            bmpbits >>= (x%8);
            bmpbits &= mask;
            switch(op){
                case BMP_COPY:
                    video_buffer[y][idx] &= ~mask;
                    video_buffer[y][idx] |= bmpbits;
                    break;
                case BMP_OR:
                    video_buffer[y][idx] |= bmpbits;
                    break;
                case BMP_AND:
                    video_buffer[y][idx] &= (~mask) | bmpbits;
                    break;
                case BMP_XOR:
                    video_buffer[y][idx] ^= bmpbits;
                    break;
            }//switch
            x += mwidth;
            xbmp += mwidth;
            bitsleft -= mwidth;
        }//while
        ybmp+=ybmp_inc;
        
    }//for

//    awidth=width/8;
//    if (width%8) awidth++;
//    first= left/8;
//    lmask= 0xff>>(left%8);
//    last= (left+width-1)/8;
//    if (width<9){
//        if (8-left%8>=width){
//            rmask= lmask;
//        }else{
//            rmask= 0xff<<(8-left%8);
//        }//if
//    }
//    else{
//        rmask=0xff<<(8-(left+width)%8);
//    }//if
//    if (first==last){
//        lmask &= rmask;
//        for (i=top;i<top+height;i++){
//            switch(r2op){
//                case BMP_COPY:
//                    video_buffer[i][first] &= ~lmask;
//                    video_buffer[i][first] |= (*(bmp+(i-top)))>>(left%8);
//                    break;
//                case BMP_OR:
//                    video_buffer[i][first] |= (*(bmp+(i-top)))>>(left%8);
//                    break;
//                case BMP_AND:
//                    video_buffer[i][first] &= ~(lmask^((*(bmp+(i-top)))>>(left%8)));
//                    break;
//                case BMP_XOR:
//                    video_buffer[i][first] ^= (*(bmp+(i-top)))>>(left%8);
//                    break;
//            }//switch
//        }//for
//    }else{
//        for (i=top;i<top+height;i++){
//            switch(r2op){
//                case BMP_COPY:
//                    video_buffer[i][first] &= ~lmask;
//                    video_buffer[i][first] |= (*(bmp+(i-top)))>>(left%8);
//                    video_buffer[i][last] &= ~rmask;
//                    if (width<8)
//                        video_buffer[i][last]|=(*(bmp+(i-top)*awidth+awidth-1))<<(width-1-(left+width-1)%8);
//                    else
//                        video_buffer[i][last] |=(*(bmp+(i-top)*awidth+awidth-1))<<(7-(left+width-1)%8);
//                    break;
//                case BMP_OR:
//                    video_buffer[i][first] |= (*(bmp+(i-top)))>>(left%8);
//                    if (width<8)
//                        video_buffer[i][last]|=(*(bmp+(i-top)*awidth+awidth-1))<<(width-1-(left+width-1)%8);
//                    else
//                        video_buffer[i][last] |=(*(bmp+(i-top)*awidth+awidth-1))<<(7-(left+width-1)%8);
//                    break;
//                    break;
//                case BMP_AND:
//                    video_buffer[i][first] &= ~(lmask^((*(bmp+(i-top)))>>(left%8)));
//              //      video_buffer[i][last] &= ~(rmask^(*(bmp+(i-top)*awidth+awidth-1)));
//                    if (width<8)
//                        video_buffer[i][last]&=~(rmask^(*(bmp+(i-top)*awidth+awidth-1))<<(width-1-(left+width-1)%8));
//                    else
//                        video_buffer[i][last] &=~(rmask^(*(bmp+(i-top)*awidth+awidth-1))<<(7-(left+width-1)%8));
//                    break;
//                case BMP_XOR:
//                    video_buffer[i][first] ^= (*(bmp+(i-top)*awidth+awidth-1))>>(left%8);
//                    if (width<8)
//                        video_buffer[i][last] ^=(*(bmp+(i-top)*awidth+awidth-1))<<(width-1-(left+width-1)%8);
//                    else
//                        video_buffer[i][last] ^=(*(bmp+(i-top)*awidth+awidth-1))<<(7-(left+width-1)%8);
//                    break;
//            }//switch
//        }//for
//        if (last>first+1){
//            for (i=top;i<top+height;i++){
//                for (j=first+1;j<last;j++){
//                    switch(r2op){
//                        case BMP_COPY:
//                            video_buffer[i][j]= *(bmp+(i-top)*awidth+j);
//                            break;
//                        case BMP_OR:
//                            video_buffer[i][j] |= *(bmp+(i-top)*awidth+j);
//                            break;
//                        case BMP_AND:
//                            video_buffer[i][j] &= *(bmp+(i-top)*awidth+j);
//                            break;
//                        case BMP_XOR:
//                            video_buffer[i][j] ^= *(bmp+(i-top)*awidth+j);
//                            break;
//                    }//switch
//                }//for
//            }//for
//        }//if
//    }
}//f()
