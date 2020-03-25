#include "Lab_5.h"

void main(){
    
   // Setting up PIC modules such as Timers, IOs OCs,Interrupts, ...
    InitializeIO(); 
   // InitializeLEDs();
    InitializeTimers();
    while(1) // endless loop
    {
        WaitOnBtn1();
       // pooling ==> the instructions are executed within this infinite loop
        Forward(4.0,70);
        Stop(1.0);
        
        Backward(3.0,60);
        Stop(2);
        Forward(3.0,50);
        Stop(1.0);
        Backward(3.0,30);
        LEDsOFF();   
    }  
    return;
}

void InitializeIO(){
    //Btn IOs
    TRISAbits.TRISA6 = 1; 
    TRISAbits.TRISA7 = 1;
    
    
    //LED IOs
    TRISBbits.TRISB10=0;
    TRISBbits.TRISB11=0;
    TRISBbits.TRISB12=0;
    TRISBbits.TRISB13 =0;
    LATBCLR = 0x3C00; // trun off all LEDs

    // H-Bridge
    TRISGbits.TRISG12 = 0;
    TRISGbits.TRISG13 = 0;
    LATGbits.LATG12 = 0; 
    LATGbits.LATG13 = 0; 
    return; 
}

void InitializeTimers(){
    // Initialize Timer1
    T1CON = 0x0000; // Set Timer1 Control to zeros
    T1CONbits.TCKPS=3; // prescale by 256
    T1CONbits.ON = 1; // Turn on Timer
    PR1= 0xFFFF; // Period of Timer1 to be full
    TMR1 = 0; // Initialize Timer1 to zero
    // Initialize Timer2
    T2CON = 0;
    T2CONbits.TCKPS = 7; // prescale by 256
    T2CONbits.T32 = 1; // use 32 bits timer
    T2CONbits.ON = 1;
    PR2 = 0xFFFFFFFF; // Period is set for 32 bits
    TMR2 = 0;
}
void WaitOnBtn1(){
 while(PORTAbits.RA6 == 0) // wait on Btn1 indefinitely
 ;
 LATBbits.LATB10 = 1; // Turn On LED1 inidicating it is Btn1 is Pushed
 return;
}


void Forward(float Sec, int D){
    int RunTime = (int)(Sec*39000); // convert the total time to number of Tics
    TMR2 = 0;
    LATGbits.LATG12 = 1;  // forward Direction
    LATBbits.LATB12 = 0; // LED 3 is OFF
    LATBbits.LATB13 = 0; // LED 4 is OFF
    LATBbits.LATB11 = 1; // LED 2 is OFF
    while (TMR2 < RunTime){
        PWM(D);
        ;
    }
    
    return;
}
void Backward(float Sec, int D){
    
	// Enter your code here
     int RunTime = (int)(Sec*39000); // convert the total time to number of Tics
    TMR2 = 0;
    LATGbits.LATG12 = 0;  // forward Direction
    LATBbits.LATB12 = 1; // LED 3 is OFF
    LATBbits.LATB13 = 0; // LED 4 is OFF
    LATBbits.LATB11 = 0; // LED 2 is OFF
    while (TMR2 < RunTime){
        PWM(D);
        ;
    }
    return;
}

void PWM(int D){
    // enter your code
    TMR1 = 0;
    int Period = 400;
    while (TMR1< Period) {
        if (TMR1 < Period*D/100){
            LATGbits.LATG13 = 1;
        }
        else{
            LATGbits.LATG13 = 0;
        }
    }
    return;
}
void Stop(float Sec){
    int RunTime = (int)(Sec*39000); // convert the total time to number of Tics
    TMR2 = 0;
    LATGbits.LATG12 = 1;  // forward Direction
     LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1; 
    
    while (TMR2 < RunTime){
      LATGbits.LATG13 = 0;
    }
    
    return;
}

void LEDsOFF(){
     
    LATBbits.LATB10 = 0; 
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;  
    return;     
}