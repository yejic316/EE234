/* 
 * File:   Lab_8.h
 * Author: Yejic
 *
 * Created on November 7, 2017, 5:01 PM
 */

#ifndef LAB_8_H
#define	LAB_8_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "xc.h"
#include <sys/attribs.h> 


//Configure the clock
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits Primary PLL System
#pragma config POSCMOD = EC // Uses external circuit
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (1x Divider) 

void UART2_Setup();
void U2MODE_Config();
void U2STAT_Config();
void U2INT_Config();
void Initialize_Timer2();
void Initialize_OC();

void Wait500ms(); 
void EnableInterrupt();
void LEDsOFF(); 
void IO_Setup();

void Stop();
void Move_NW();
void Move_N();
void Move_NE();
void Move_E();
void Move_W();
void Move_SW();
void Move_SE();
void Move_S();

typedef enum{NW, N, NE,W, STOP, E, SW, S, SE} Direction;
Direction Dir= STOP;



#ifdef	__cplusplus
}
#endif

#endif	/* LAB_8_H */

