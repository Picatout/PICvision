/*
* Copyright 2014, Jacques Desch�nes
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
 * File:   snake.c
 * Author: jacques Desch�nes
 * Description: snake game in text mode.
 * Created on 5 mars 2014, 16:01
 */

#include <stdlib.h>
#include <time.h>
#include "../../PICvision.h"

typedef struct symbol{
    unsigned char x;
    unsigned char y;
    char part;
}symbol_t;

#define SNAKE_MAX_LEN  64

typedef struct snake_struct{
    unsigned length;
    unsigned calories;
    unsigned lifespan;
    unsigned short dx;
    unsigned short dy;
    symbol_t body[SNAKE_MAX_LEN];
}snake_t;

// snake some symbols
#define RING  102+32
#define HEAD_RIGHT  103+32
#define HEAD_LEFT 104+32
#define HEAD_UP  105+32
#define HEAD_DOWN 106+32
#define MOUSE 109+32

#define BASE_METABOLISM 2   // calories lost per seconde
#define MOUSE_CALORIES  20  // calories gain by eating mouse

static snake_t snake;

static symbol_t mouse;

static int run; // game exit when run==0

const msg_t msgCALORIES={0,0,"calories: "};
const msg_t msgSECONDS={16,0,"lifespan: "};
const msg_t msgGAME_OVER={6,13,"game over"};
const msg_t msgSTART={8,20, "press START to begin"};
const msg_t msgQUIT={8,21,"X to quit game."};
const msg_t msgSTARVATION={6,14,"died of starvation"};
const msg_t msgWALL_COLLIDE={6,14,"died of wall collision"};
const msg_t msgTAIL_BITE={6,14,"died of tail bite."};


static void new_mouse(){
    unsigned short i, collide,mouseX,mouseY;
    collide=1;
    while (collide){
        mouseX=rand()%(CHAR_PER_LINE-3)+2;
        mouseY=rand()%(LINE_PER_SCREEN-3)+2;
        for (i=0;i<snake.length;i++){
            if ((mouseX==snake.body[i].x)&&(mouseY==snake.body[i].y)) break;
        }
        if (i==snake.length) collide=0;
    }//while
    mouse.x=mouseX;
    mouse.y=mouseY;
    set_curpos(mouse.x,mouse.y);
    put_char(mouse.part);
}//f()

static void hide_snake(){
    unsigned i;
    for (i=0;i<snake.length;i++){
        set_curpos(snake.body[i].x,snake.body[i].y);
        put_char(SPACE);
    }
}//f()

static void show_snake(){
    unsigned i;
    for (i=0;i<snake.length;i++){
        set_curpos(snake.body[i].x,snake.body[i].y);
        put_char(snake.body[i].part);
        
    }//for
}//f()


static int wait_start_signal(){
    unsigned p;
    p=0;
    print_msg(msgSTART);
    print_msg(msgQUIT);
    while (1){
      p=read_paddle(PADDLE1);
      if ((p&SNES_START)==SNES_START){
          return 1;
      }else if ((p&SNES_X)==SNES_X){
          return 0;
      }
    }
}//f()

static void animate_death(){
    int i,freq;
    show_snake();
    freq=snake.length*200;
    for (i=snake.length-1;i>=0;i--){
        set_curpos(snake.body[i].x,snake.body[i].y);
        put_char(32);
        tone(freq,250);
        wait_n_frame(frames_per_second/4);
        freq -= 100;
    }//for
}//f()

// dead cause
typedef enum DEATH {STARVATION,WALL_COLLISION,TAIL_BITE} death_t;

static unsigned char reset=0;
static void game_over(death_t cause){
    animate_death();
    print_msg(msgGAME_OVER);
    switch (cause){
        case STARVATION:
            print_msg(msgSTARVATION);
            break;
        case WALL_COLLISION:
            print_msg(msgWALL_COLLIDE);
            break;
        case TAIL_BITE:
            print_msg(msgTAIL_BITE);
            break;
    }//switch
    reset=1;
    if (!wait_start_signal()) run=0;
}//f()

static void add_calories(unsigned short gain){
    snake.calories+=gain;
    print_msg(msgCALORIES);
    print_int(snake.calories,1);
}//f()


static void burn_calories(unsigned short lost){
    unsigned newLength;
    if (lost < BASE_METABOLISM) lost=BASE_METABOLISM;
    snake.calories -= lost;
    if (snake.calories<0) snake.calories=0;
    print_msg(msgCALORIES);
    clear_eol();
    print_int(snake.calories,1);
    print_msg(msgSECONDS);
    print_int(snake.lifespan,1);
    hide_snake();
    newLength=snake.calories/MOUSE_CALORIES+1;
    if (snake.calories){
        snake.length=newLength+1;
        show_snake();
    } else{
        game_over(STARVATION);
        return;
    }
}//f()

static void check_if_got_mouse(){
    if ((mouse.x==snake.body[0].x) && (mouse.y==snake.body[0].y)){
        add_calories(MOUSE_CALORIES);
        snake.length++;
        snake.body[snake.length-1].part=RING;
        if (snake.dx){
            if (snake.body[snake.length-2].y==snake.body[0].y){
                snake.body[snake.length-1].x=snake.body[snake.length-2].x-snake.dx;
                snake.body[snake.length-1].y=snake.body[snake.length-2].y;
            }else{
                snake.body[snake.length-1].x=snake.body[snake.length-2].x;
                if (snake.body[0].y>snake.body[snake.length-2].y){
                    snake.body[snake.length-1].y=snake.body[snake.length-2].y-1;
                }else{
                    snake.body[snake.length-1].y=snake.body[snake.length-2].y+1;
                }//if
            }//if
        }else {
            if (snake.body[snake.length-2].x==snake.body[0].x){
                snake.body[snake.length-1].x=snake.body[snake.length-2].x;
                snake.body[snake.length-1].y=snake.body[snake.length-2].y-snake.dy;
            }else{
                snake.body[snake.length-1].y=snake.body[snake.length-2].y;
                if (snake.body[0].x>snake.body[snake.length-2].x){
                    snake.body[snake.length-1].x=snake.body[snake.length-2].x-1;
                }else{
                    snake.body[snake.length-1].x=snake.body[snake.length-2].x+1;
                }//if
            }//if

        }//if
        new_mouse();
    }
}//f()

static int bit_himself(){
    int i;
    for (i=1;i<snake.length;i++){
        if ((snake.body[0].x==snake.body[i].x) &&(snake.body[0].y==snake.body[i].y)){
            return 1;
        }
    }
    return 0;
}//f()

static void move_snake(){
    unsigned i;
    if (!(snake.dx || snake.dy)) return;
    hide_snake();
    for (i=snake.length-1;i;i--){
        snake.body[i].x = snake.body[i-1].x;
        snake.body[i].y = snake.body[i-1].y;
    }
    snake.body[0].x += snake.dx;
    snake.body[0].y += snake.dy;
    if ((snake.body[0].x<1)||(snake.body[0].x>=(CHAR_PER_LINE)) ||
        (snake.body[0].y<2) || (snake.body[0].y>=LINE_PER_SCREEN-1)){
        game_over(WALL_COLLISION);
    }else if (bit_himself()){
        game_over(TAIL_BITE);
    }else{
        check_if_got_mouse();
        show_snake();
    }//if
}//f()

static void game_info(){
    clear_screen();
    print("**************\r");
    print("* SNAKE GAME *\r");
    print("**************\r\r");
    print("Eating a mouse increase snake length.\r");
    print("Snake burn 10% of is calaries/sec.\r");
    print("Die of starvation when calories=0.\r");
    print("Eating a mouse give 20 calories.\r");
    print("Die when hitting wall.\r");
    print("Die when bitting his tail.\r\r");
    print("Use ARROWS to control snake.\r");
    run=wait_start_signal();
}//f()

static void game_init(){
    reset=0;
    srand(time(0));
    //snake initialisation
    snake.dx=0;
    snake.dy=0;
    snake.length=2;
    snake.calories=MOUSE_CALORIES;
    snake.lifespan=0;
    snake.body[0].x=12;
    snake.body[0].y=12;
    snake.body[0].part=HEAD_RIGHT;
    snake.body[1].x=11;
    snake.body[1].y=12;
    snake.body[1].part=RING;
    mouse.part=MOUSE;
    clear_screen();
    print_msg(msgCALORIES);
    print_int(snake.calories,1);
    print_msg(msgSECONDS);
    print_int(snake.lifespan,1);
    //draw  borders
    rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
    new_mouse();
    show_snake();
}//f()


void snake_game_tm(void) {
    unsigned p,frame_count;
    game_info();
    game_init();
    frame_count=0;
    while (run){
        wait_n_frame(10);
        frame_count += 10;
        if (frame_count%frames_per_second==0){
            snake.lifespan +=1;
            burn_calories(snake.calories / 10);
            rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
        }
        p=read_paddle(PADDLE1);
        switch (p){
            case SNES_LEFT:
                if (snake.dx==1){
                    break;
                }
                snake.dx =-1;
                snake.dy=0;
                snake.body[0].part=HEAD_LEFT;
                break;
            case SNES_RIGHT:
                if (snake.dx==-1){
                    break;
                }
                snake.dx=1;
                snake.dy=0;
                snake.body[0].part=HEAD_RIGHT;
                break;
            case SNES_UP:
                if (snake.dy==1){
                    break;
                }
                snake.dy=-1;
                snake.dx=0;
                snake.body[0].part=HEAD_UP;
                break;
            case SNES_DOWN:
                if (snake.dy==-1){
                    break;
                }
                snake.dy=1;
                snake.dx=0;
                snake.body[0].part=HEAD_DOWN;
                break;
        }//switch
        move_snake();
        if (reset) game_init();
    }//while
    clear_screen();
}//snake_game_tm()

