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
 * File:   2048.h
 * Author: jacques Deschênes
 * Description:  implementation on PICvision of Gabriele Cirulli 2048 game
 * game website: http://gabrielecirulli.github.io/2048/
 *
 * Created on 23 avril 2014, 15:58
 */

#include <stdlib.h>

#include "../../PICvision.h"

#define BOARD_LEFT (0)
#define BOARD_TOP  (1)

unsigned board[16];  // game board

unsigned current_score, max_score;

static unsigned cell_width, cell_height;

void draw_board(){
    unsigned x,y, rect_width,rect_height;
    //rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
    rect_width=cell_width*CHAR_WIDTH-2;
    rect_height=cell_height*CHAR_HEIGHT-2;
    for (y=0;y<4;y++){
        for (x=0;x<4;x++){
            rectangle(x*rect_width+2*(x+1),y*rect_height+2*(y+1)+CHAR_HEIGHT,
                      x*rect_width+2*(x+1)+rect_width,
                      y*rect_height+2*(y+1)+CHAR_HEIGHT+rect_height, WHITE);
        }
    }
}//f()

void print_board_values(){
    unsigned i,x,y;
    for (i=0;i<16;i++){
        if (board[i]){
            x=(i&3)*cell_width+2;
            y=(i>>2)*cell_height+(cell_height>>1)+1;
            set_curpos(x,y);
            print_int(board[i],0);
        }
    }//for
}//f()

void pop_number(){ // add a number to the board
    unsigned pos;
    do{
        pos=rand()&15;
    }while (board[pos]);
    board[pos]=((rand()&1)+1)<<1;
}//f()

void init_board_values(){
    unsigned pos;
    for (pos=0;pos<16;pos++){
        board[pos]=0;
    }
    pop_number();
    pop_number();
}//f()

BOOL is_movable(){// check if a move is possible
    return 1;
}//f()

int update_value(int x,int y, int t){
    int sum=0;
    if (!board[(y<<2)+x]){
        board[(y<<2)+x]=board[(t<<2)+x];
        board[(t<<2)+x]=0;
    }else if (board[(y<<2)+x]==board[(t<<2)+x]){
        board[(y<<2)+x] <<= 1;
        sum = board[(y<<2)+x];
        board[(t<<2)+x]=0;
    }else if (t>(y+1)){
        board[((y+1)<<2)+x]=board[(t<<2)+x];
        board[(t<<2)+x]=0;
    }
    return sum;
}//f()

void slide_tiles(unsigned arrow){// move numbers on board way of arrow
    int x,y,t,sum;
    sum=0;
    arrow &= SNES_UP|SNES_DOWN|SNES_LEFT|SNES_RIGHT;
    switch(arrow){
        case SNES_UP:
            for(x=0;x<4;x++){
                for(y=0;y<3;y++){
                    t=y+1;
                    while ((t<4) && !board[(t<<2)+x]){
                        t++;
                    }
                    if (t==4) break;
                    sum += update_value(x,y,t);
                }
            }
            break;
        case SNES_DOWN:
            for (x=0;x<4;x++){
                for (y=3;y;y--){
                    t=y-1;
                    while ((t>=0)&&(!board[(t<<2)+x])){
                        t--;
                    }
                    if (t<0) break;
                    sum += update_value(x,y,t);
                }
            }
            break;
        case SNES_LEFT:
            for (y=0;y<4;y++){
                for (x=0;x<3;x++){
                    t=x+1;
                    while (t<4 && !board[(y<<2)+t]){
                        t++;
                    }
                    if (t==4)break;
                    sum += update_value(x,y,t);
                }
            }
            break;
        case SNES_RIGHT:
            for (y=0;y<4;y++){
                for (x=3;x;x--){
                    t=x-1;
                    while((t>=0)&&(!board[(y<<2)+t])){
                        t--;
                    }
                    if (t<0) break;
                    sum += update_value(x,y,t);
                }
            }
            break;
    }//switch
    current_score += sum;
}//f()

void update_board(){
    clear_screen();
    draw_board();
    print_board_values();
    set_curpos(0,24);
    print("score: ");
    print_int(current_score,0);
    set_curpos(0,25);
    print("best score: ");
    print_int(max_score,0);
}//f()

BOOL game_over(){
    unsigned key;
    box(0,0,HPIXELS,VPIXELS-3*CHAR_HEIGHT,BLACK);
    set_curpos(12,12);
    print("game over");
    set_curpos(0,14);
    print("START for new game, X to leave.");
    do{
        key=read_paddle(PADDLE1);
    } while (!key);
    if (key & SNES_X) return 1; else return 0;
}//f()

void gc_2048_game(void){
    unsigned key;
    cell_width=CHAR_PER_LINE/4; // size in character
    cell_height=LINE_PER_SCREEN/4 ; // height in lines count
    if (!(cell_height&1)) cell_height--;
    init_board_values();
    update_board();
    while (1){
        wait_n_frame(2);
        do {
            key=read_paddle(PADDLE1);
        } while (!key);
        if (key & SNES_X) break;
        slide_tiles(key);
        update_board();
        if (!is_movable()){
            if (game_over()) break;
        }
        pop_number();
        while (read_paddle(PADDLE1));
    }//while
}//f()


