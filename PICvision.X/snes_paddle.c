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
 * Created on 25 février 2014, 16:41
 */

#include <stdlib.h>
#include "snes_paddle.h"
#include "TVout.h"

#define mNOP()  asm("nop")
#define mLATCH() {P_PDL_LATCH=1;mNOP();mNOP();P_PDL_LATCH=0;}
#define mCLK_HIGH() (P_PDL_CLK=1)
#define mCLK_LOW()  (P_PDL_CLK=0)
#define mSHIFT() {mCLK_HIGH();mNOP();mNOP();mCLK_LOW();mNOP();mNOP();}

volatile static unsigned pdl_last_read[2], pdl_last_state[2];


void read_paddles() {
    int i,pdata;
    pdl_last_state[PADDLE1]=0;
    pdl_last_state[PADDLE2]=0;
    mLATCH(); // latch data in paddles shift register
    // shift out is least significant bit first.
    for (i=0;i<16;i++){ // SNES paddle have 16 bits shift register
        mSHIFT();
        pdata=PADDLES_DATA_PORT;
        pdl_last_state[PADDLE1] |= (pdata&PADDLE1)<<i;
        pdl_last_state[PADDLE2] |= (pdata&PADDLE2)?1<<i:0;
    }
}//f()

void paddle_init(){
    read_paddles();
    pdl_last_read[PADDLE1]=pdl_last_state[PADDLE1];
    pdl_last_read[PADDLE2]=pdl_last_state[PADDLE2];
}// f()


unsigned read_paddle(int paddleId){
    read_paddles();
    // wait a stable state (debounce)
    while (pdl_last_read[paddleId]!=pdl_last_state[paddleId]){
        pdl_last_read[PADDLE1]=pdl_last_state[PADDLE1];
        pdl_last_read[PADDLE2]=pdl_last_state[PADDLE2];
        wait_n_frame(1);
        read_paddles();
    }// while
    pdl_last_read[PADDLE1]=pdl_last_state[PADDLE1];
    pdl_last_read[PADDLE2]=pdl_last_state[PADDLE2];
    return pdl_last_read[paddleId];
}//f()
