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
 * File:   font.c
 * Description: police de caract�re  5x7
 * Author: Jacques Desc�nes
 *
 * Created on 7 septembre 2013, 16:28
 */

#include "font.h"
const unsigned char font6x8[FONT_SIZE][CHAR_HEIGHT]={
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // espace
	{0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00}, // !
	{0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00}, // "
	{0x14,0x14,0x3e,0x14,0x3e,0x14,0x14,0x00}, // #
	{0x08,0x1e,0x28,0x1c,0x0a,0x3c,0x08,0x00}, // $
	{0x30,0x32,0x04,0x08,0x10,0x26,0x06,0x00}, // %
	{0x18,0x24,0x28,0x10,0x2a,0x24,0x1a,0x00}, // &
	{0x18,0x08,0x10,0x00,0x00,0x00,0x00,0x00}, // '
	{0x04,0x08,0x10,0x10,0x10,0x08,0x04,0x00}, // (
	{0x10,0x08,0x04,0x04,0x04,0x08,0x10,0x00}, // )
	{0x00,0x08,0x2a,0x1c,0x2a,0x08,0x00,0x00}, // *
	{0x00,0x08,0x08,0x3e,0x08,0x08,0x00,0x00}, // +
	{0x00,0x00,0x00,0x00,0x18,0x08,0x10,0x00}, // ,
	{0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00}, // -
	{0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, // .
	{0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00}, // /
	{0x1c,0x22,0x26,0x2a,0x32,0x22,0x1c,0x00}, // 0
	{0x08,0x18,0x08,0x08,0x08,0x08,0x3e,0x00}, // 1
	{0x1c,0x22,0x04,0x08,0x10,0x20,0x3e,0x00}, // 2
	{0x3c,0x02,0x02,0x3c,0x02,0x02,0x3c,0x00}, // 3
	{0x04,0x0c,0x14,0x24,0x3e,0x04,0x04,0x00}, // 4
	{0x3e,0x20,0x20,0x3c,0x02,0x02,0x3c,0x00}, // 5
	{0x0c,0x10,0x20,0x3c,0x22,0x22,0x1c,0x00}, // 6
	{0x3e,0x02,0x04,0x08,0x10,0x10,0x10,0x00}, // 7
	{0x1c,0x22,0x22,0x1c,0x22,0x22,0x1c,0x00}, // 8
	{0x1c,0x22,0x22,0x1c,0x02,0x02,0x1c,0x00}, // 9
	{0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x00}, // :
	{0x00,0x18,0x18,0x00,0x18,0x08,0x10,0x00}, // ;
	{0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x00}, // <
	{0x00,0x00,0x3e,0x00,0x3e,0x00,0x00,0x00}, // =
	{0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x00}, // >
	{0x1c,0x22,0x02,0x04,0x08,0x00,0x08,0x00}, // ?
	{0x1c,0x22,0x02,0x1a,0x2a,0x2a,0x1c,0x00}, // @
	{0x1c,0x22,0x22,0x3e,0x22,0x22,0x22,0x00}, // A
	{0x3c,0x22,0x22,0x3c,0x22,0x22,0x3c,0x00}, // B
	{0x1e,0x20,0x20,0x20,0x20,0x20,0x1e,0x00}, // C
	{0x3c,0x22,0x22,0x22,0x22,0x22,0x3c,0x00}, // D
	{0x3e,0x20,0x20,0x3e,0x20,0x20,0x3e,0x00}, // E
	{0x3e,0x20,0x20,0x3e,0x20,0x20,0x20,0x00}, // F
	{0x1e,0x20,0x20,0x2c,0x22,0x22,0x1c,0x00}, // G
	{0x22,0x22,0x22,0x3e,0x22,0x22,0x22,0x00}, // H
	{0x1c,0x08,0x08,0x08,0x08,0x08,0x1c,0x00}, // I
	{0x1e,0x02,0x02,0x02,0x02,0x24,0x18,0x00}, // J
	{0x22,0x24,0x28,0x30,0x28,0x24,0x22,0x00}, // K
	{0x20,0x20,0x20,0x20,0x20,0x20,0x3e,0x00}, // L
	{0x22,0x36,0x2a,0x22,0x22,0x22,0x22,0x00}, // M
	{0x22,0x22,0x32,0x2a,0x26,0x22,0x22,0x00}, // N
	{0x1c,0x22,0x22,0x22,0x22,0x22,0x1c,0x00}, // O
	{0x3c,0x22,0x22,0x3c,0x20,0x20,0x20,0x00}, // P
	{0x1c,0x22,0x22,0x22,0x2a,0x26,0x1e,0x00}, // Q
	{0x3c,0x22,0x22,0x3c,0x28,0x24,0x22,0x00}, // R
	{0x1e,0x20,0x20,0x1c,0x02,0x02,0x3c,0x00}, // S
	{0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x00}, // T
	{0x22,0x22,0x22,0x22,0x22,0x22,0x1c,0x00}, // U
	{0x22,0x22,0x22,0x22,0x22,0x14,0x08,0x00}, // V
	{0x22,0x22,0x22,0x2a,0x2a,0x36,0x22,0x00}, // W
	{0x22,0x22,0x14,0x08,0x14,0x22,0x22,0x00}, // X
	{0x22,0x22,0x22,0x14,0x08,0x08,0x08,0x00}, // Y
	{0x3e,0x04,0x08,0x10,0x20,0x20,0x3e,0x00}, // Z
	{0x18,0x10,0x10,0x10,0x10,0x10,0x18,0x00}, // [
	{0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00}, // '\'
	{0x06,0x02,0x02,0x02,0x02,0x02,0x06,0x00}, // ]
	{0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x00}, // ^
	{0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00}, // _
	{0x10,0x08,0x04,0x00,0x00,0x00,0x00,0x00}, // `
        {0x00,0x00,0x1c,0x02,0x1e,0x22,0x1e,0x00}, // a
        {0x20,0x20,0x20,0x2c,0x32,0x22,0x3c,0x00}, // b
        {0x00,0x00,0x1c,0x20,0x20,0x22,0x1c,0x00}, // c
        {0x02,0x02,0x02,0x1a,0x26,0x22,0x1e,0x00}, // d
        {0x00,0x00,0x1c,0x22,0x3e,0x20,0x1c,0x00}, // e
        {0x0c,0x12,0x10,0x38,0x10,0x10,0x10,0x00}, // f
        {0x00,0x00,0x1e,0x22,0x22,0x1e,0x02,0x1c}, // g
        {0x20,0x20,0x2c,0x32,0x22,0x22,0x22,0x00}, // h
        {0x00,0x08,0x00,0x08,0x08,0x08,0x08,0x00}, // i
        {0x04,0x00,0x0c,0x04,0x04,0x24,0x18,0x00}, // j
        {0x20,0x20,0x24,0x28,0x30,0x28,0x24,0x00}, // k
        {0x18,0x08,0x08,0x08,0x08,0x08,0x1c,0x00}, // l
        {0x00,0x00,0x34,0x2a,0x2a,0x22,0x22,0x00}, // m
        {0x00,0x00,0x2c,0x32,0x22,0x22,0x22,0x00}, // n
        {0x00,0x00,0x1c,0x22,0x22,0x22,0x1c,0x00}, // o
        {0x00,0x00,0x3c,0x22,0x22,0x3c,0x20,0x20}, // p
        {0x00,0x00,0x1a,0x24,0x24,0x2c,0x14,0x06}, // q
        {0x00,0x00,0x2c,0x32,0x20,0x20,0x20,0x00}, // r
        {0x00,0x00,0x1c,0x20,0x1c,0x02,0x3c,0x00}, // s
        {0x10,0x10,0x38,0x10,0x10,0x12,0x0c,0x00}, // t
        {0x00,0x00,0x22,0x22,0x22,0x26,0x1a,0x00}, // u
        {0x00,0x00,0x22,0x22,0x22,0x14,0x08,0x00}, // v
        {0x00,0x00,0x22,0x22,0x2a,0x2a,0x14,0x00}, // w
        {0x00,0x00,0x22,0x14,0x08,0x14,0x22,0x00}, // x
        {0x00,0x00,0x22,0x22,0x22,0x1e,0x02,0x1c}, // y
        {0x00,0x00,0x3e,0x04,0x08,0x10,0x3e,0x00}, // z
        {0x08,0x10,0x10,0x20,0x10,0x10,0x08,0x00}, // {
        {0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00}, // |
        {0x10,0x08,0x08,0x04,0x08,0x08,0x10,0x00}, // }
        {0x00,0x00,0x10,0x2a,0x04,0x00,0x00,0x00}, // ~
        {0x3e,0x22,0x22,0x22,0x22,0x22,0x3e,0x00}, // 95 rectangle
        {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}, // 96 left vertical bar
        {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01}, // 97 right vertical bar
        {0x3f,0x20,0x20,0x20,0x20,0x20,0x20,0x20}, // 98 top-left corner
        {0x3f,0x01,0x01,0x01,0x01,0x01,0x01,0x01}, // 99 top-right corner
        {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3f}, // 100 bottom-left corner
        {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x3f}, // 101 bottom-right corner
        {0x00,0x0c,0x1e,0x3f,0x3f,0x1e,0x0c,0x00}, // 102 ball
        {0x0e,0x1b,0x3e,0x3c,0x3e,0x3f,0x1e,0x00}, // 103 head right
        {0x1c,0x36,0x1f,0x0f,0x1f,0x3e,0x1e,0x00}, // 104 head left
        {0x21,0x3b,0x2f,0x3f,0x1e,0x0c,0x0c,0x00}, // 105 head up
        {0x0c,0x0c,0x1e,0x3f,0x2f,0x3b,0x21,0x00}, // 106 head down
        {0x00,0x00,0x18,0x25,0x02,0x00,0x00,0x00}, // 107 tail horizontal
        {0x04,0x02,0x04,0x08,0x08,0x04,0x00,0x00}, // 108 tail vertical
        {0x00,0x00,0x02,0x17,0x2f,0x07,0x02,0x00}, // 109 mouse
};