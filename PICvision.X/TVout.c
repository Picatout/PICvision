/* 
 * File:   TVout.c
 * Author: jacques Deschênes
 * Description:  NTSC/PAL signal generator
 * Created on 25 février 2014, 16:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TVout.h"


#define HPERIOD 1016  // timer count for 15748Hz horizontal frequency ( no prescale)
#define HPULSE 75 // 4,7µsec horizontal pulse width
#define FIRST_VISIBLE 28 // première ligne visible
#define LAST_VISIBLE (FIRST_VISIBLE+VPIXELS) // dernière ligne visible

#define F_PCHAR 1    // flag put_char() pending
#define F_CLEAR 2    // flag clear_screen() pending
#define F_CLREOL 4   // flag clear to end of line
#define F_RETRACE 8 // flag screen in retrace phase

#define QUEUE_SIZE 32  // put_char queue

static unsigned int frame_line_cntr=0; // count line in video frame
volatile static unsigned long frame_cntr=0; // number of frame since reset
volatile static unsigned int flags;

typedef union coord_type{
    unsigned int yx;
    struct{
        unsigned char y;
        unsigned char x;
    };
}coord_t;

volatile static coord_t cursor_pos;

volatile static char pchar_queue[QUEUE_SIZE];

char video_buffer[LINES][COLUMNS];
volatile static unsigned  head=0, tail=0;


void  video_init(){ // initialisation sorties NTSC
    T2CON=0; // désactivation TIMER2
    PR2 = HPERIOD;
    // OC1 video sync
    OC1R=HPULSE;
    OC1RS=HPERIOD;
    OC1CON=5; // mode 5, timer 2
    //OC3 video delay timer
    OC3R=2*HPULSE;
    OC3RS=HPERIOD-16;
    OC3CON=5; // mode 5, timer 2
    // OC1 interrupt service  routine trigger video pixels output via SPI1
    IFS0bits.OC1IF=0;
    IPC0bits.OC1IP=7;
    // timer 2 interrupt enabling
    IFS0bits.T2IF=0;
    IPC1bits.T2IP=7; // plus haute priorité
    IEC0bits.T2IE=1;
    // SPI1 configuratio (pixel output)
    SPI1CON1=0;
    SPI1CON1bits.DISSCK=1;
    SPI1CON1bits.MSTEN=1;
    SPI1CON1bits.SPRE=7;
    SPI1CON1bits.PPRE=2;
    SPI1CON2=1;
    SPI1STATbits.SPIEN=1;
    T2CONbits.TON=1;
    cursor_pos.y=0;
    cursor_pos.x=0;
}//horz_sync_init()

void  wait_n_frame(unsigned n){
unsigned long f0;
    f0=frame_cntr+n;
    while (frame_cntr<f0);
}//f()

void clear_screen(){ // clear screen
    flags |= F_CLEAR;
    while (flags & F_CLEAR);
}//f()

void clear_eol(){// clear line from cursor to end of line
    flags |= F_CLREOL;
}//f()

void move_cursor(unsigned line, unsigned column){
    cursor_pos.y=line;
    cursor_pos.x=column;
}//f()

unsigned get_cursor(){
    return cursor_pos.yx;
}//f()

void put_char(char c){// put character at current cursor position & move cursor forward
    pchar_queue[tail++]=c;
    tail %= QUEUE_SIZE;
    flags |= F_PCHAR;
}//f()

void print(const char *str){
    while (*str){
        put_char(*str++);
    }
}//f()

void wait_while_printing(){
    while (flags & F_PCHAR);
}//f()

void scroll_up(){ //scroll screen 1 line up
    memmove((char*)video_buffer,(char*)video_buffer[1],sizeof(char)*COLUMNS*(LINES-1));
    memset((char*)video_buffer[LINES-1],0,sizeof(char)*COLUMNS);
}//f()

void cursor_forward(){
    cursor_pos.x++;
    if (cursor_pos.x>=COLUMNS){
        cursor_pos.x=0;
        cursor_pos.y++;
        if (cursor_pos.y>=LINES){
            cursor_pos.y--;
            scroll_up();
        }//if
    }//if
}//f()

// video sync signal generation
void __attribute__((interrupt,no_auto_psv,shadow)) _T2Interrupt(void){
    frame_line_cntr++;
    switch (frame_line_cntr){
        case 1:
            OC1R=HPERIOD-HPULSE;
            break;
        case 4:
            OC1R=HPULSE;
            break;
        case FIRST_VISIBLE:
            IFS0bits.OC1IF=0;
            IEC0bits.OC1IE=1;
            //SPI1STATbits.SPIEN=1;
            flags &= ~F_RETRACE;
            break;
        case LAST_VISIBLE:
            IEC0bits.OC1IE=0;
            //SPI1STATbits.SPIEN=0;
            flags |= F_RETRACE;
            break;
        case 263:
            frame_line_cntr=0;
            frame_cntr++;
            break;
        default:
            if (flags & F_RETRACE){
                if (flags & F_CLEAR){
                    memset((char*)video_buffer,0,sizeof(char)*LINES*COLUMNS);
                    flags &= ~F_CLEAR;
                    cursor_pos.y=0;
                    cursor_pos.x=0;
                } else if (flags & F_CLREOL){
                    memset((char*)video_buffer[cursor_pos.y]+cursor_pos.x,
                            0,sizeof(char)*(COLUMNS-cursor_pos.x));
                    flags &= ~F_CLREOL;
                }else if (flags & F_PCHAR){
                    video_buffer[cursor_pos.y][cursor_pos.x]=pchar_queue[head]-32;
                    cursor_forward();
                    head++;
                    head %= QUEUE_SIZE;
                    if (head==tail){
                        flags &= ~F_PCHAR;
                    }
                }//if
            }//if
            break;
    }//switch
    IFS0bits.T2IF=0;
}// _T2Interrupt()

// video pixels output
void __attribute__((interrupt,no_auto_psv,shadow)) _OC1Interrupt(void){
    int y,x,l;
    char *b;
    y=(frame_line_cntr-FIRST_VISIBLE)>>3;
    l=(frame_line_cntr-FIRST_VISIBLE)&7;
    b=(char*)&video_buffer[y];
    while (!PORTBbits.RB11);
    for (x=0;x<COLUMNS;x++){
        while (SPI1STATbits.SPITBF);
        SPI1BUF=font6x8[(int)*b++][l];
    }//for
    while (SPI1STATbits.SPITBF);
    SPI1BUF=0;
    IFS0bits.OC1IF=0;
}// _OC1Interrupt()

