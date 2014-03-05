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
 * File:   snes_paddle.c
 * Author: jacques Deschênes
 * Description:  SNES gemepad interface
 *              1) a pulse on paddle latch input store last switches state in shift register
 *              2) each rising edge of clock signal shift one bit out, bit 0 first.
 *                 bit 0 is at output after latch so there is only 15 shift to do.
 * Created on 25 février 2014, 16:41
 */

#include <stdlib.h>
#include "snes_paddle.h"
//#include "TVout.h"



// the loop execute in 4 Tcy
#define mDelay(usec) __asm__("MOV #%0,W4\n NOP\n DEC W4,W4\n BRA NZ .-4"::"i"(usec))

void latch(){
    P_PDL_LATCH=1;
    mDelay(CYCLES_PER_USEC/4);
    P_PDL_LATCH=0;
    mDelay(CYCLES_PER_USEC/4);
}//f()

void bit_shift(){
    P_PDL_CLK=1;
    mDelay(CYCLES_PER_USEC/4);
    P_PDL_CLK=0;
    mDelay(CYCLES_PER_USEC/4);
}// f()

unsigned read_paddle(int paddleId) {
    unsigned i,pdata, p1,p2;
    p1=0;
    p2=0;
    latch(); // latch data in paddles shift register
    // shift out is least significant bit first.
    for (i=0;i<15;i++){ // SNES paddle have 16 bits shift register
        pdata=PADDLES_DATA_PORT;
        p1 |= (pdata&PADDLE1)<<i;
        p2 |= (pdata&PADDLE2)?1<<i:0;
        bit_shift();
    }
    return paddleId==1?(~p1)&0xfff:(~p2)&0xfff;
}//f()

