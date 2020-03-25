/* 
 * File:   Lab_6.h
 * Author: Yejic
 *
 * Created on October 10, 2017, 4:24 PM
 */

#ifndef LAB_6_H
#define	LAB_6_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>
#include <sys/attribs.h>  


//Configure the clock
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits Primary PLL System
#pragma config POSCMOD = EC // Uses external circuit
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (1x Divider) 

//typedef enum{Forward, Stop1, Backward, Stop2, TurnRight, Stop3, TurnLeft, Stop4} Mode;

//Mode Move = Forward; 



void Enable_Interrupt();
void Initialize_OC();
void Initialize_Timer2();
void Initialize_IO();
void Move_Forward();
void Move_Backward();
void Stop();
void Turn_Right();
void Turn_Left();


#ifdef	__cplusplus
}
#endif

#endif	/* LAB_6_H */

