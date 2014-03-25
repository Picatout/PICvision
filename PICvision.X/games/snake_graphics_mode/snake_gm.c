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
 * File:   snake.c
 * Author: jacques Deschênes
 * Description: snake game graphics mode
 * Created on 24 mars 2014, 19:28
 */

#include <time.h>
#include "../../PICvision.h"

#include "snake_gm.h"
#include "resources/snake_head_down.xbm"
#include "resources/snake_head_up.xbm"
#include "resources/snake_head_left.xbm"
#include "resources/snake_head_right.xbm"
#include "resources/mouse.xbm"
#include "resources/snake_segment_up_down.xbm"
#include "resources/snake_segment_left_right.xbm"

#define HEAD_UP     0
#define HEAD_RIGHT  1
#define HEAD_DOWN   2
#define HEAD_LEFT   3
#define SEG_HORZ    4
#define SEG_VERT    5
#define MOUSE       6

#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16

static unsigned char *sprites[7]={snake_head_up_bits,snake_head_right_bits,
snake_head_down_bits,snake_head_left_bits,snake_segment_left_right_bits,
snake_segment_up_down_bits,mouse_bits};

typedef struct symbol{
    unsigned char x;  //{left,top corner coordinates}
    unsigned char y;
    char sprite;      // sprites array index
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



#define BASE_METABOLISM 2   // calories lost per seconde
#define MOUSE_CALORIES  20  // calories gain by eating mouse

snake_t snake;

symbol_t mouse;

int run; // game exit when run==0

const msg_t msgCALORIES_GM={0,0,"calories: "};
const msg_t msgSECONDS_GM={16,0,"lifespan: "};
const msg_t msgGAME_OVER_GM={6,13,"game over"};
const msg_t msgSTART_GM={8,20, "press START to begin"};
const msg_t msgQUIT_GM={8,21,"X to quit game."};
const msg_t msgSTARVATION_GM={6,14,"died of starvation"};
const msg_t msgWALL_COLLIDE_GM={6,14,"died of wall collision"};
const msg_t msgTAIL_BITE_GM={6,14,"died of tail bite."};

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
    xbm(mouse.x,mouse.y,SPRITE_WIDTH,SPRITE_HEIGHT,sprites[mouse.sprite]);
}//f()

static void hide_snake(){
    unsigned i;
    for (i=0;i<snake.length;i++){
        box(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,BLACK);
    }
}//f()

static void show_snake(){
    unsigned i;
    for (i=0;i<snake.length;i++){
        set_curpos(snake.body[i].x,snake.body[i].y);
        xbm(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,
            sprites[snake.body[i].sprite]);
    }//for
}//f()


static int wait_start_signal(){
    unsigned p;
    p=0;
    print_msg(msgSTART_GM);
    print_msg(msgQUIT_GM);
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
        box(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,BLACK);
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
    print_msg(msgGAME_OVER_GM);
    switch (cause){
        case STARVATION:
            print_msg(msgSTARVATION_GM);
            break;
        case WALL_COLLISION:
            print_msg(msgWALL_COLLIDE_GM);
            break;
        case TAIL_BITE:
            print_msg(msgTAIL_BITE_GM);
            break;
    }//switch
    reset=1;
    if (!wait_start_signal()) run=0;
}//f()

static void add_calories(unsigned short gain){
    snake.calories+=gain;
    print_msg(msgCALORIES_GM);
    print_int(snake.calories,1);
}//f()


static void burn_calories(unsigned short lost){
    unsigned newLength;
    if (lost < BASE_METABOLISM) lost=BASE_METABOLISM;
    snake.calories -= lost;
    if (snake.calories<0) snake.calories=0;
    print_msg(msgCALORIES_GM);
    clear_eol();
    print_int(snake.calories,1);
    print_msg(msgSECONDS_GM);
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
        snake.body[snake.length-1].sprite=snake.body[snake.length-2].sprite;
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
    snake.body[0].x=100;
    snake.body[0].y=100;
    snake.body[0].sprite=HEAD_LEFT;
    snake.body[1].x=116;
    snake.body[1].y=100;
    snake.body[1].sprite=SEG_HORZ;
    mouse.sprite=MOUSE;
    clear_screen();
    print_msg(msgCALORIES_GM);
    print_int(snake.calories,1);
    print_msg(msgSECONDS_GM);
    print_int(snake.lifespan,1);
    //draw  borders
    rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
    new_mouse();
    show_snake();
}//f()


void snake_game_gm(void) {
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
                snake.body[0].sprite=HEAD_LEFT;
                break;
            case SNES_RIGHT:
                if (snake.dx==-1){
                    break;
                }
                snake.dx=1;
                snake.dy=0;
                snake.body[0].sprite=HEAD_RIGHT;
                break;
            case SNES_UP:
                if (snake.dy==1){
                    break;
                }
                snake.dy=-1;
                snake.dx=0;
                snake.body[0].sprite=HEAD_UP;
                break;
            case SNES_DOWN:
                if (snake.dy==-1){
                    break;
                }
                snake.dy=1;
                snake.dx=0;
                snake.body[0].sprite=HEAD_DOWN;
                break;
        }//switch
        move_snake();
        if (reset) game_init();
    }//while
    clear_screen();
}//snake_game_gm()

