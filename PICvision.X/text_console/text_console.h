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

#ifndef TEXT_CONSOLE_H
#define	TEXT_CONSOLE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "../TVout/TVout.h"
#include "font.h"

#define LINE_PER_SCREEN ((int)VPIXELS/CHAR_HEIGHT)
#define CHAR_PER_LINE ((int)(HPIXELS/CHAR_WIDTH)-1)
#define TAB_WIDTH 4

#define ESC 27
#define CR  13
#define LF  10
#define TAB 9
#define SPACE 32

typedef struct{
    unsigned short x;
    unsigned short y;
} text_coord_t;

typedef struct msg_struct{
    unsigned char x;
    unsigned char y;
    char *text;
}msg_t;

typedef enum _CURSOR_SHAPE {CR_UNDER=0,CR_BLOCK} cursor_t;


// text_console API
void clear_screen(void); // clear screen and move cursor at {0,0}
void clear_eol(void); // clear end of line from cursor.
void scroll_up(void); // scroll text 1 line up.
void scroll_down(void); // scroll text 1 line down.
text_coord_t get_curpos(); // return text cursor position.
void set_curpos(unsigned short x, unsigned short y); // set text cursor position
void put_char(unsigned char c); //put character at current cursor position
void print(const char *str); // print string at current cursor position
void print_hex(unsigned int i, unsigned char width); // print integer in HEX format at current position
void print_int(int number, unsigned short width); // print integer at current position.
void cursor_right(void); // move text cursor 1 position right.
void cursor_left(void); // move text cursor 1 position left.
void cursor_down(void); // move text cursor 1 line down scroll_up() if needed.
void cursor_up(void); // move text cursor 1 line up, scroll_down() if needed.
void set_tab_width(unsigned char width); // set tab width.
void invert_char(void); // invert pixels of character at cursor position.
void show_cursor(BOOL); // display cursor
void set_cursor(cursor_t shape); // set cursor shape (underscore or block)
void crlf(void); // move cursor at beginning of next line
void invert_video(); // set inverse video mode for text.
void normal_video(); // set normal video mode for text.
void print_msg(const msg_t msg); // print message at fixed position.

#ifdef	__cplusplus
}
#endif

#endif	/* TEXT_CONSOLE_H */

