/* 
 * File:   Lab_7.h
 * Author: Yejic
 *
 * Created on October 24, 2017, 4:38 PM
 */

#ifndef LAB_7_H
#define	LAB_7_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>             /* contains Vector Name/Number Macros */
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include <stdio.h>

/* Oscillator Settings
*/
#pragma config FNOSC = PRIPLL // Oscillator selection
#pragma config POSCMOD = EC // Primary oscillator mode
#pragma config FPLLIDIV = DIV_2 // PLL input divider
#pragma config FPLLMUL = MUL_20 // PLL multiplier
#pragma config FPLLODIV = DIV_1 // PLL output divider
#pragma config FPBDIV = DIV_8 // Peripheral bus clock divider

typedef enum{Forward, Stop1, Backward,Stop2, Turn,Stop3} Mode;
Mode mode= Forward;

void  InitializeSystem();
void Initialize_IO();
void Initialize_Timer1();
void Initialize_Timer2();
void Initialize_Timer3(); 
void Initialize_OC();
void Initialize_IC();
void InitializeADC();
void Interrupts_enable();

// used by ADC
void  ReadADC();
void Motor_Forward();
void Check_Speed();
void Stop(); 
void Motor_Backward(); 
void Turning();

unsigned int speed1=1000, speed2=1000;
unsigned int TempT1=0, TempT2=0;
unsigned int d1=0, d2=0;


#ifdef	__cplusplus
}
#endif

#endif	/* LAB_7_H */

