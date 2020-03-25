/* 
 * File:   Lab_5.h
 * Author: Yejic
 *
 * Created on October 3, 2017, 6:42 PM
 */

#ifndef LAB_5_H
#define	LAB_5_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

//Configure the clock
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits Primary PLL System
#pragma config POSCMOD = EC // Uses external circuit
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (1x Divider)       


// Functions Prototypes
void InitializeIO(); 
//void InitializeLEDs();
void InitializeTimers();
void WaitOnBtn1();
void Forward(float Sec,int D);
void PWM(int D);
void Stop(float Sec);
void Backward(float Sec, int D);
void LEDsOFF();


#ifdef	__cplusplus
}
#endif

#endif	/* LAB_5_H */

