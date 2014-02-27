/* 
 * File:   TVout.h
 * Author: jacques Deschênes
 * Description:  NTSC/PAL signal generator
 *
 * Created on 25 février 2014, 16:28
 */

#ifndef TVOUT_H
#define	TVOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <PPS.h>
#include "hardwareProfile.h"
#include "font.h"

#define NTSC

#ifdef NTSC
#define VPERIOD 17
#else
#define VPERIOD 20
#endif

#define VPIXELS 216
#define HPIXELS 200
#define LINES (VPIXELS/8)
#define COLUMNS (HPIXELS/8)


void  video_init();
void  wait_n_frame(unsigned n);

void clear_screen();
void clear_eol();
void move_cursor(unsigned line, unsigned column);
unsigned  get_cursor();
void put_char(char c);
void print(const char *str);
void wait_while_printing();


#ifdef	__cplusplus
}
#endif

#endif	/* TVOUT_H */

