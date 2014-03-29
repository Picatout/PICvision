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

#include "snake.h"
#include "resources/snake_head_down.xbm"
#include "resources/snake_head_up.xbm"
#include "resources/snake_head_left.xbm"
#include "resources/snake_head_right.xbm"
#include "resources/mouse.xbm"
#include "resources/snake_segment.xbm"

#define HEAD_NORTH  0
#define HEAD_EAST   1
#define HEAD_SOUTH  2
#define HEAD_WEST   3
#define SEGMENT     4
#define MOUSE       5

#define SPRITE_WIDTH  16
#define SPRITE_HEIGHT 16

const unsigned char * const sprites[7]={snake_head_up_bits,snake_head_right_bits,
snake_head_down_bits,snake_head_left_bits,snake_segment_bits,mouse_bits};


typedef struct sprite{
    unsigned char x;  //{left,top corner coordinates}
    unsigned char y;
    union{
    unsigned char heading;  // direction of displacement
    unsigned char sprite;  // sprites array index
    };
    char spare; // alignement
}sprite_t;

#define SNAKE_MAX_LEN  32

typedef struct snake_struct{
    unsigned length;
    unsigned calories;
    unsigned lifespan;
    unsigned speed;
    sprite_t body[SNAKE_MAX_LEN];
}snake_t;



#define BASE_METABOLISM 2   // calories lost per seconde
#define MOUSE_CALORIES  20  // calories gain by eating mouse

snake_t snake;
sprite_t mouse;  // mouse sprite
static int run; // game exit when run==0
static unsigned char reset=0; // reinitialize game

static const msg_t msgCALORIES={0,0,"calories: "};
static const msg_t msgSECONDS={18,0,"lifespan: "};
static const msg_t msgGAME_OVER={6,13,"game over"};
static const msg_t msgSTART={8,20, "press START to begin"};
static const msg_t msgQUIT={8,21,"X to quit game."};
static const msg_t msgSTARVATION={6,14,"died of starvation"};
static const msg_t msgWALL_COLLIDE={6,14,"died of wall collision"};
static const msg_t msgTAIL_BITE={6,14,"died of tail bite."};


static int collision(int x1, int y1, int x2, int y2){
    int dx, dy;
    dx = x1-x2;
    if (dx<0) dx = -dx;
    dy = y1-y2;
    if (dy<0) dy= -dy;
    if ((dx<SPRITE_WIDTH) && (dy<SPRITE_HEIGHT)) return 1; else return 0;
}//f()

static void hide_mouse(){
    box((unsigned)mouse.x,(unsigned)mouse.y,SPRITE_WIDTH,SPRITE_HEIGHT,BLACK);
}// f()

static void new_mouse(){
    unsigned short i, collide,mouseX,mouseY;
    collide=1;
    while (collide){
        mouseX=rand()%(HPIXELS-SPRITE_WIDTH-3)+2;
        mouseY=rand()%(HPIXELS-CHAR_HEIGHT-19)+CHAR_HEIGHT+2;
        for (i=0;i<snake.length;i++){
            if (collision(mouseX,mouseY,snake.body[i].x,snake.body[i].y)) break;
        }
        if (i==snake.length) collide=0;
    }//while
    mouse.x=mouseX;
    mouse.y=mouseY;
    put_xbm(mouse.x,mouse.y,SPRITE_WIDTH,SPRITE_HEIGHT,sprites[mouse.heading]);
}//f()

static void hide_snake(){
    unsigned i;
    set_curpos(0,2);
    for (i=0;i<snake.length;i++){
        box(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,BLACK);
    }
}//f()

static void show_snake(){
    unsigned i;
    put_xbm(snake.body[0].x,snake.body[0].y,SPRITE_WIDTH,SPRITE_HEIGHT,
            sprites[snake.body[0].heading]);
    for (i=1;i<snake.length;i++){
        put_xbm(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,
            sprites[SEGMENT]);
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
    freq=2000;
    for (i=snake.length-1;i>=0;i--){
        box(snake.body[i].x,snake.body[i].y,SPRITE_WIDTH,SPRITE_HEIGHT,BLACK);
        tone(freq,100);
        wait_n_frame(frames_per_second/10);
        freq -= 100;
    }//for
}//f()

// dead cause
typedef enum DEATH {STARVATION,WALL_COLLISION,TAIL_BITE} death_t;

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

void display_status(){
    print_msg(msgCALORIES);
    clear_eol();
    print_int(snake.calories,1);
    print_msg(msgSECONDS);
    print_int(snake.lifespan,1);
    //draw  borders
    rectangle(0,CHAR_HEIGHT,HPIXELS-1,VPIXELS-1,WHITE);
}//f()

static void add_calories(unsigned short gain){
    snake.calories+=gain;
    display_status();
}//f()


static void burn_calories(unsigned short lost){
    if (lost < BASE_METABOLISM) lost=BASE_METABOLISM;
    snake.calories -= lost;
    if (snake.calories<0) snake.calories=0;
    display_status();
    hide_snake();
    if (snake.calories){
        show_snake();
    } else{
        game_over(STARVATION);
    }
}//f()

const unsigned int BYTE_SOUND[]={100,100,64,100,0,0};

static void check_if_got_mouse(){
    if (collision(mouse.x,mouse.y,snake.body[0].x,snake.body[0].y)){
        hide_mouse();
        tune(BYTE_SOUND);
        add_calories(MOUSE_CALORIES);
        if (snake.length<SNAKE_MAX_LEN){
            snake.length++;
            snake.body[snake.length-1].heading=snake.body[snake.length-2].heading;
            snake.body[snake.length-1].x=snake.body[snake.length-2].x;
            snake.body[snake.length-1].y=snake.body[snake.length-2].y;
        }
        //while_sound();
        //tone(64,100);
        new_mouse();
    }//if
}//f()

static int bit_himself(){
    int i;
    for (i=3;i<snake.length;i++){
        if (collision(snake.body[0].x,snake.body[0].y,
                     snake.body[i].x,snake.body[i].y)){
            return 1;
        }
    }
    return 0;
}//f()

static void move_snake(){
    unsigned i;

    hide_snake();
    for (i=snake.length-1;i;i--){
        snake.body[i].x = snake.body[i-1].x;
        snake.body[i].y = snake.body[i-1].y;
        snake.body[i].heading = snake.body[i-1].heading;
    }
    switch (snake.body[0].heading){
        case HEAD_NORTH:
            if (snake.body[0].y>=snake.speed+CHAR_HEIGHT)
                snake.body[0].y -= snake.speed;
            else
                snake.body[0].y=CHAR_HEIGHT;
            break;
        case HEAD_EAST:
            if (snake.body[0].x<HPIXELS-SPRITE_WIDTH-snake.speed)
                snake.body[0].x += snake.speed;
            else
                snake.body[0].x=HPIXELS-SPRITE_WIDTH;
            break;
        case HEAD_SOUTH:
            if (snake.body[0].y<VPIXELS-SPRITE_HEIGHT-snake.speed)
                snake.body[0].y += snake.speed;
            else
                snake.body[0].y=VPIXELS-SPRITE_HEIGHT;
            break;
        case HEAD_WEST:
            if (snake.body[0].x>=snake.speed)
                snake.body[0].x -= snake.speed;
            else
                snake.body[0].x=0;
            break;
    }//switch
    if ((snake.body[0].x<1)||(snake.body[0].x>=(HPIXELS-SPRITE_WIDTH)) ||
        (snake.body[0].y<CHAR_HEIGHT+2) || (snake.body[0].y>=VPIXELS-SPRITE_HEIGHT)){
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
    //snake initialisation
    snake.length=2;
    snake.calories=MOUSE_CALORIES;
    snake.lifespan=0;
    snake.speed=16;
    snake.body[0].x=100;
    snake.body[0].y=100;
    snake.body[0].heading=rand()%4;
    snake.body[1].heading=snake.body[0].heading;
    switch(snake.body[0].heading){
        case HEAD_NORTH:
            snake.body[1].x=snake.body[0].x;
            snake.body[1].y=snake.body[0].y+SPRITE_HEIGHT;
            break;
        case HEAD_EAST:
            snake.body[1].x=snake.body[0].x-SPRITE_WIDTH;
            snake.body[1].y=snake.body[0].y;
            break;
        case HEAD_SOUTH:
            snake.body[1].x=snake.body[0].x;
            snake.body[1].y=snake.body[0].y-SPRITE_HEIGHT;
            break;
        case HEAD_WEST:
            snake.body[1].x=snake.body[0].x+SPRITE_WIDTH;
            snake.body[1].y=snake.body[0].y;
            break;
    }//switch
    mouse.sprite=MOUSE;
    clear_screen();
    display_status();
    new_mouse();
    show_snake();
}//f()


void snake_game(void) {
    unsigned p,frame_count;
    game_info();
    srand(get_frame_count());
    reset=1;
    frame_count=0;
    while (run){
        if (reset) game_init();
        wait_n_frame(10);
        frame_count += 10;
        if (frame_count%frames_per_second==0){
            snake.lifespan +=1;
            burn_calories(snake.calories / 10);
        }
        p=read_paddle(PADDLE1);
        switch (p){
            case SNES_LEFT:
                if (snake.body[0].heading==HEAD_EAST){
                    break;
                }
                snake.body[0].heading =HEAD_WEST;
                break;
            case SNES_RIGHT:
                if (snake.body[0].heading==HEAD_WEST){
                    break;
                }
                snake.body[0].heading=HEAD_EAST;
                break;
            case SNES_UP:
                if (snake.body[0].heading==HEAD_SOUTH){
                    break;
                }
                snake.body[0].heading=HEAD_NORTH;
                break;
            case SNES_DOWN:
                if (snake.body[0].heading==HEAD_NORTH){
                    break;
                }
                snake.body[0].heading=HEAD_SOUTH;
                break;
            default: ;
        }//switch
        move_snake();
    }//while
    clear_screen();
}//snake_game_gm()

