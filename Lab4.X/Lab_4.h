/* 
 * File:   Lab4_h.h
 * Author: Yejic
 *
 * Created on September 26, 2017, 4:57 PM
 */

#ifndef LAB4_H_H
#define	LAB4_H_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
//Configure the clock
#pragma config FNOSC = PRIPLL  // Oscillator Selection Bits Primary PLL System
#pragma config POSCMOD = EC  // Uses external circuit
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)

// Functions Prototypes
void InitializeIO();
void InitializeTimer1();
void WaitOnBtn1(); 
void BlinkingLEDs();

unsigned int T2= 29296;
unsigned int T3= 19531; 
unsigned int T4= 9765; 

unsigned int count_T2=0;
unsigned int count_T3=0;


#ifdef	__cplusplus
}
#endif

#endif	/* LAB4_H_H */

