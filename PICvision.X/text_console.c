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
 * File:   text_console.h
 * Author: jacques Deschênes
 * Description: manage text writing in video_buffer
 * Created on 28 février 2014, 10:04
 */

#include <stdlib.h>
#include <string.h>
#include "text_console.h"

//static text_coord_t cursor_pos;

//#define X_OFS  ((HPIXELS-CHAR_PER_LINE*CHAR_WIDTH)/2)  // x offset to cursor from screen edge
//#define Y_OFS  ((VPIXELS-LINE_PER_SCREEN*CHAR_HEIGHT)/2) // y offset to cursor from screen edge

// boolean flags
#define CUR_SHOW 1  // cursor active
#define CUR_VIS  2  // cursor state visible
#define INV_VID  4  // invert video


static unsigned short cx=0, cy=0;  // coordonnée courante du curseur texte en pixels.
static unsigned char tab_width=TAB_WIDTH;
static cursor_t cur_shape=CR_UNDER;
static unsigned short flags=0;



void scroll_up(void){
    char *src, *dst;
    dst = (char*)video_buffer;
    src = (char*)video_buffer + CHAR_HEIGHT*BYTES_PER_LINE;
    memmove(dst,src,(LINE_PER_SCREEN-1)*CHAR_HEIGHT*BYTES_PER_LINE);
    dst= (char*)video_buffer+(CHAR_HEIGHT*(LINE_PER_SCREEN-1))*BYTES_PER_LINE;
    memset(dst,0,HPIXELS/8*CHAR_HEIGHT);
}//scroll_up();

void scroll_down(void){
    char *src, *dst;
    src = (char*)video_buffer;
    dst = (char*)video_buffer+CHAR_HEIGHT*BYTES_PER_LINE;
    memmove(dst,src,(LINE_PER_SCREEN-1)*CHAR_HEIGHT*BYTES_PER_LINE);
    dst=(char*)video_buffer;
    memset(dst,0,HPIXELS/8*CHAR_HEIGHT);
}//scroll_down()


void cursor_right(void){
    cx += CHAR_WIDTH;
    if (cx>(CHAR_PER_LINE*CHAR_WIDTH)){
        cx = 0;
        cy += CHAR_HEIGHT;
        if (cy>(LINE_PER_SCREEN*CHAR_HEIGHT)){
            scroll_up();
            cy -= CHAR_HEIGHT;
        }
    }
} // cursor_right()

void cursor_left(void){
    if (cx>=CHAR_WIDTH){
        cx -= CHAR_WIDTH;
    }else{
        cx = CHAR_WIDTH*(CHAR_PER_LINE-1);
        if (cy>=CHAR_HEIGHT){
            cy -= CHAR_HEIGHT;
        }else{
            scroll_down();
        }
    }
}// cursor_left()

void cursor_up(void){
    if (cy>=CHAR_HEIGHT){
        cy -= CHAR_HEIGHT;
    }else{
        scroll_down();
    }
}// cursor_up()

void cursor_down(void){
    if (cy<=(CHAR_HEIGHT*(LINE_PER_SCREEN-2))){
        cy += CHAR_HEIGHT;
    }else{
        scroll_up();
    }
}//cursor_down()

void crlf(void){
    cx=0;
    if (cy==(LINE_PER_SCREEN-1)*CHAR_HEIGHT){
        scroll_up();
    }else{
        cy += CHAR_HEIGHT;
    }
}//crlf()

void put_char(unsigned char c){
    register int i,l,r,b,x,y;
    x=cx;
    y=cy;
    switch (c){
        case CR:
            crlf();
            break;
        case TAB:
            cx += (cx%tab_width);
            if (cx>=(CHAR_PER_LINE*CHAR_WIDTH)){
                cx = 0;
                if (cy==(LINE_PER_SCREEN-1)*CHAR_HEIGHT){
                    scroll_up();
                }else{
                    cy += CHAR_HEIGHT;
                }
            }
            break;
        case '\b':
            cursor_left();
            break;
        default:
            if ((c<32) || (c>=(FONT_SIZE+32))) break;
            c -=32;
            b=x>>3; // character position in video_buffer
            r=0;
            l=(8-CHAR_WIDTH)-(x&7); // shift inside this byte
            if (l<0){
                r=-l;
            }
            for (i=0;i<8;i++){
                if (r){
                    if (flags & INV_VID){
                        video_buffer[y][b] |= (0x3f>>r);
                        video_buffer[y][b] &=~(font6x8[(int)c][i]>>r);
                        video_buffer[y][b+1] |= (0x3f<<(8-r));
                        video_buffer[y][b+1] &= ~(font6x8[(int)c][i]<<(8-r));
                    }else{
                        video_buffer[y][b] &= ~(0x3f>>r);
                        video_buffer[y][b] |= font6x8[(int)c][i]>>r;
                        video_buffer[y][b+1] &= ~(0x3f<<(8-r));
                        video_buffer[y][b+1] |= font6x8[(int)c][i]<<(8-r);
                    }
                    y++;
                } else{
                    if (flags & INV_VID){
                        video_buffer[y][b] |= (0x3f<<l);
                        video_buffer[y++][b] &=~(font6x8[(int)c][i]<<l);
                    }else{
                        video_buffer[y][b] &= ~(0x3f<<l);
                        video_buffer[y++][b] |= font6x8[(int)c][i]<<l;
                    }
                }
            }
            cursor_right();
    }//switch(c)
}//put_char()

void clear_screen(){
    memset(video_buffer,0,HPIXELS/8*VPIXELS);
    cx=0;
    cy=0;
} // clear_screen()

void print(const char *text){
    while (*text){
        put_char(*text++);
    }
}// print()

void print_hex(unsigned int hex, unsigned char width){
    char c[12], *d;
    int i;
    c[11]=0;
    d= &c[10];
    for(i=width;i>=0||hex;i--){
        *d=(hex%16);
        if (*d<10)
            *d += '0';
        else
            *d += 'A'-10;
        hex /=16;
        d--;
    }
    print(++d);
} // print_hex()

void print_int(int number, unsigned short width){ // imprime entier,width inclus le signe
    int sign=0, i;
    char str[14], *d;
    str[13]=0;
    d=&str[12];
    if (width>13){width=13;}
    if (number<0){
        sign=1;
        number = -number;
    }
    //for (i=--width;i>=0||number;i--){
    i=width;
    while (number>0){
       *d--=(number%10)+'0';
        number /= 10;
        i--;
    }
    if (i==width){
        *d--='0';
        i--;
    }
    while (i>0){
        *d--=' ';
        i--;
    }
    if (sign){*d='-';}else{*d=' ';}
    print(d);
}// print_int()

void set_tab_width(unsigned char width){
    tab_width=width;
}// set_tab_width()

void clear_eol(void){
    int x,y;
    x=cx;
    y=cy;
    while (cx<(CHAR_WIDTH*(CHAR_PER_LINE-2))){
        put_char(32);
    }
    put_char(32);
    cx=x;
    cy=y;
}// clear_eol()

text_coord_t get_curpos(){
    text_coord_t cpos;
    cpos.x = cx/CHAR_WIDTH;
    cpos.y = cy/CHAR_HEIGHT;
    return cpos;
} // get_cursor_pos()

void set_curpos(unsigned short x, unsigned short y){// {x,y} character coord.
    if (x>(CHAR_PER_LINE-1) || y>(LINE_PER_SCREEN-1))
        return;
    cx=x*CHAR_WIDTH;
    cy=y*CHAR_HEIGHT;
}//set_curpos()

void invert_char(void){// invert pixels of character at cursor position
    register int i,l,r,b,x,y;
    x=cx;
    y=cy;
    b=x>>3;
    r=0;
    l=(8-CHAR_WIDTH)-(x&7);
    if (l<0){
        r=-l;
    }
    for (i=9;i;i--){
        if (r){
            video_buffer[y][b] ^= (0x3f>>r);
            video_buffer[y][b+1] ^= (0x3f<<(8-r));
            y++;
        } else{
            video_buffer[y++][b] ^= (0x3f<<l);
        }
    }
}//invert_char()

static void toggle_underscore(void){
    register int l,r,b,x;
    x=cx;
    b=x>>5;
    r=0;
    l=(8-CHAR_WIDTH)-(x&7);
    if (l<0){
        r=-l;
    }
    if (r){
        video_buffer[cy+CHAR_HEIGHT-1][b] ^= (0x3f>>r);
        video_buffer[cy+CHAR_HEIGHT-1][b+1] ^= (0x3f<<(8-r));
    } else{
        video_buffer[cy+CHAR_HEIGHT-1][b] ^= (0x3f<<l);
    }
}//toggle_underscore()

void show_cursor(BOOL show){
    if (show){
        flags |= CUR_SHOW;
        flags ^= CUR_VIS;
        if (cur_shape==CR_BLOCK){
            invert_char();
        }else{
            toggle_underscore();
        }
    }else{
        if (flags & CUR_VIS){
            if (cur_shape==CR_BLOCK){
                invert_char();
            }else{
                toggle_underscore();
            }
            flags &= ~CUR_VIS;
        }
        flags &= ~CUR_SHOW;
    }

}// show_cursor()

void set_cursor(cursor_t shape){
    if (flags & CUR_VIS){
        show_cursor(FALSE);
        cur_shape=shape;
        show_cursor(TRUE);
    }else{
        cur_shape=shape;
    }
}// set_cursor()


void invert_video(){
    flags |= INV_VID;
}//invert_video()

void normal_video(){
    flags &= ~INV_VID;
}//normal_video()
