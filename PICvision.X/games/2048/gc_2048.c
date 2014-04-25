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

unsigned current_score=0, max_score=0;

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
    srand(get_frame_count());
    pop_number();
    pop_number();
    if (current_score>max_score){
        max_score=current_score;
    }
    current_score=0;
}//f()

BOOL is_playable(){// check if a move is possible
    int i;
    for (i=0;i<16;i++){
        if (!board[i]) return 1;
    }
    for (i=0;i<12;i++){
        if ((i&3)==3){
            if (board[i]==board[i+4]) return 1;
        }else if ((board[i]==board[i+1])||(board[i]==board[i+4])) return 1;

    }
    return 0;
}//f()

unsigned congratulation(int x, int y){
    unsigned key, t,line,column;
    BOOL vstate=FALSE;
    set_curpos(0,22);
    print("CONGRATULATION! YOU GOT 2048 SUM!");
    crlf();
    print("'A' to continue, 'B' new game.");
    line=y*cell_height+(cell_height>>1)+1;
    column=x*cell_width+2;
    t=get_frame_count()+30;
    while(read_paddle(PADDLE1)){
        wait_n_frame(1);
    }
    do{
        if (get_frame_count()>t){
            set_curpos(column,line);
            if (!vstate){
                invert_video();
            }else{
                normal_video();
            }
            vstate = !vstate;
            print(" 2048");
            t=get_frame_count()+30;
        }
        key=read_paddle(PADDLE1);
    } while (!key);
    normal_video();
    set_curpos(column,line);
    print(" 2048");
    set_curpos(6,22);
    clear_eol();
    crlf();
    clear_eol();
    if ((key & SNES_B)==SNES_B){
        return 2;
    }else{
        return 1;
    }
}//f()


int slide_tiles(unsigned arrow){// move numbers on board
    int x,y,t,sum,bound;
    unsigned state; // 0=no change, 1=changed, 2=start new game
    sum=0;
    state=0;
    arrow &= SNES_UP|SNES_DOWN|SNES_LEFT|SNES_RIGHT;
    switch(arrow){
        case SNES_UP:
            for(x=0;x<4;x++){
                bound=0;
                for(y=0;y<4;y++){
                    t=y;
                    while ((t<4) && !board[(t<<2)+x]){
                        t++;
                    }
                    if (t==4) break;
                    if (t>y){
                        board[(y<<2)+x]=board[(t<<2)+x];
                        board[(t<<2)+x]=0;
                        state=1;
                    }//if
                    if (y>bound){
                        if (board[((bound)<<2)+x]==board[(y<<2)+x]){
                            board[((bound)<<2)+x]<<=1;
                            sum+=board[((bound)<<2)+x];
                            board[(y<<2)+x]=0;
                            if (board[((bound)<<2)+x]==2048){
                                state=congratulation(x,bound);
                            }else{
                                state=1;
                            }
                            bound++;
                        }else if (!board[((bound)<<2)+x]){
                            board[((bound)<<2)+x]=board[(y<<2)+x];
                            board[(y<<2)+x]=0;
                            state=1;
                        }else{
                            bound++;
                            if (y>bound){
                                board[((bound)<<2)+x]=board[(y<<2)+x];
                                board[(y<<2)+x]=0;
                            }
                        }
                    }//if
                }//for
            }//for
            break;
        case SNES_DOWN:
            for (x=0;x<4;x++){
                bound=3;
                for (y=3;y>=0;y--){
                    t=y;
                    while ((t>=0)&&(!board[(t<<2)+x])){
                        t--;
                    }
                    if (t<0) break;
                    if (t<y){
                        board[(y<<2)+x]=board[(t<<2)+x];
                        board[(t<<2)+x]=0;
                        state=1;
                    }
                    if (y<bound){
                        if (board[((bound)<<2)+x]==board[(y<<2)+x]){
                            board[((bound)<<2)+x]<<=1;
                            sum+=board[((bound)<<2)+x];
                            board[(y<<2)+x]=0;
                            if (board[((bound)<<2)+x]==2048){
                                state=congratulation(x,bound);
                            }else{
                                state=1;
                            }
                            bound--;
                        }else if (!board[((bound)<<2)+x]){
                            board[((bound)<<2)+x]=board[(y<<2)+x];
                            board[(y<<2)+x]=0;
                            state=1;
                        }else{
                            bound--;
                            if (y<bound){
                                board[(bound<<2)+x]=board[(y<<2)+x];
                                board[(y<<2)+x]=0;
                            }
                        }
                    }//if
                }//for
            }//For
            break;
        case SNES_LEFT:
            for (y=0;y<4;y++){
                bound=0;
                for (x=0;x<4;x++){
                    t=x;
                    while (t<4 && !board[(y<<2)+t]){
                        t++;
                    }//while
                    if (t==4)break;
                    if (t>x){
                        board[(y<<2)+x]=board[(y<<2)+t];
                        board[(y<<2)+t]=0;
                        state=1;
                    }//if
                    if (x>bound){
                        if (board[(y<<2)+bound]==board[(y<<2)+x]){
                            board[(y<<2)+bound]<<=1;
                            sum+=board[(y<<2)+bound];
                            board[(y<<2)+x]=0;
                            if (board[(y<<2)+bound]==2048){
                                state=congratulation(bound,y);
                            }else{
                                state=1;
                            }
                            bound++;
                        }else if (!board[(y<<2)+bound]){
                            board[(y<<2)+bound]=board[(y<<2)+x];
                            board[(y<<2)+x]=0;
                            state=1;
                        }else{
                            bound++;
                            if (x>bound){
                                board[(y<<2)+bound]=board[(y<<2)+x];
                                board[(y<<2)+x]=0;
                            }
                        }
                    }//if
                }//for
            }//For
            break;
        case SNES_RIGHT:
            for (y=0;y<4;y++){
                bound=3;
                for (x=3;x>=0;x--){
                    t=x;
                    while((t>=0)&&(!board[(y<<2)+t])){
                        t--;
                    }
                    if (t<0) break;
                    if (t<x){
                        board[(y<<2)+x]=board[(y<<2)+t];
                        board[(y<<2)+t]=0;
                        state=1;
                    }//if
                    if (x<bound){
                        if (board[(y<<2)+bound]==board[(y<<2)+x]){
                            board[(y<<2)+bound]<<=1;
                            sum+=board[(y<<2)+bound];
                            board[(y<<2)+x]=0;
                            if (board[(y<<2)+bound]==2048){
                                state=congratulation(bound,y);
                            }else{
                                state=1;
                            }
                            bound--;
                        }else if (!board[(y<<2)+bound]){
                            board[(y<<2)+bound]=board[(y<<2)+x];
                            board[(y<<2)+x]=0;
                            state=1;
                        }else{
                            bound--;
                            if (x<bound){
                                board[(y<<2)+bound]=board[(y<<2)+x];
                                board[(y<<2)+x]=0;
                            }
                        }
                    }//if
                }
            }
            break;
    }//switch
    if (sum){
        invert_video();
        set_curpos(6,23);
        put_char('+');
        print_int(sum,0);
        wait_n_frame(30);
        normal_video();
    }
    current_score += sum;
    return state;
}//f()

void display_score(){
    set_curpos(0,24);
    clear_eol();
    print("score: ");
    print_int(current_score,0);
    set_curpos(0,25);
    clear_eol();
    print("best score: ");
    print_int(max_score,0);
}//f()

void update_board(){
    clear_screen();
    draw_board();
    print_board_values();
    display_score();
}//f()

BOOL game_over(){
    unsigned key;
    box(0,0,HPIXELS,VPIXELS-3*CHAR_HEIGHT,BLACK);
    display_score();
    set_curpos(12,12);
    print("game over");
    set_curpos(0,14);
    print("START for new game, X to leave.");
    do{
        key=read_paddle(PADDLE1);
    } while (!key);
    init_board_values();
    if (key & SNES_X) return 1; else return 0;
}//f()

void gc_2048_game(void){
    unsigned key,result;
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
        result=slide_tiles(key);
        if (result==1){
            pop_number();
        }else if (result==2){
            init_board_values();
        }
        update_board();
        if (!is_playable()){
            if (game_over()) break;
        }
        while (read_paddle(PADDLE1));
    }//while
}//f()


