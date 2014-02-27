/* 
 * File:   hardwareProfile.h
 * Author: jacques Desch�nes
 *
 * Created on 25 f�vrier 2014, 16:21
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>


#define FOSC 32000000UL  // 8Mhz crystal x 4 (PLL)
#define FCY  (FOSC/2)    // core cycle frequency



#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_H */

