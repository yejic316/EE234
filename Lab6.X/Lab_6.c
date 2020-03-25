
#include "Lab_6.h"
void main(){
    Initialize_IO();
    Initialize_OC();
    Initialize_Timer2();
    //while(PORTAbits.RA6==0);
    Enable_Interrupt();
    // endless loop that does nothing
    while(1){
        ;
    }
    return;
}
void Initialize_IO(){
    // Motor Direction bits
    TRISDbits.TRISD6 =0; // motor set as output
    TRISDbits.TRISD7 =0;
    TRISDbits.TRISD1 =0;
    TRISDbits.TRISD2 =0;
    LATDbits.LATD1 = 0;    
    LATDbits.LATD2 =0;
    
    //LED
    TRISBbits.TRISB10=0;
    LATBbits.LATB10=0;
    //button 
    //TRISAbits.TRISA6=1;
    //Switch
     TRISGbits.TRISG12 =1;
     TRISGbits.TRISG13 =1;
     TRISGbits.TRISG14 =1;
     TRISGbits.TRISG15 =1;

    return;
}
void Initialize_OC(){
    
         // output compare
       OC2CONbits.OCM =6;  // pwm mode with no fault protection
        OC2R = 1000;     // you may want to change this value
        OC2RS = 1000; // You may want to change this value 
        OC2CONbits.ON=1; // will turn on OC2 module
      
        OC3CONbits.OCM =6;
        OC3R = 1000;
        OC3RS = 1000;
        OC3CONbits.ON = 1;
    /* Set Interrupt Controller for multi-vector mode */
        INTCONbits.MVEC=1;

    
    return;
}
void Initialize_Timer2(){
    
    T2CONbits.TON = 0;
    T2CONbits.TCKPS = 7;
    PR2 = 3906; // may want to change this value
    TMR2 = 0;
    T2CONbits.ON =1;       

    return;
}
void Enable_Interrupt(){
 
// timer 2 interrupt enable
    IFS0bits.T2IF =0;
    IPC2bits.T2IP = 7;
    IEC0bits.T2IE = 1;
    
    INTCONbits.MVEC=1;
    __builtin_enable_interrupts();
    return;
}

void __ISR (_TIMER_2_VECTOR, IPL7SRS)  T2Interrupt(void) {
// Every time TMR2 =PR2, timer2 resets itself and this ISR is called.
	// Enter your code here

    if(TMR2 == PR2)
// Example everytime the interrupt is triggered you need to move forward. 
    {
        LATBbits.LATB10=1;

        if(PORTGbits.RG12==1) //(Move == Forward)
        {   
            Move_Forward(); 
        }
        
        else if(PORTGbits.RG13==1) // (Move == Backward)
        {
            Move_Backward(); 
        }
        else if(PORTGbits.RG14==1)// (Move == TurnRight)
        {
            Turn_Right(); 
        }
        else if(PORTGbits.RG15==1) //(Move == TurnLeft)
        {
            Turn_Left(); 
            //Move=0;
        }
        else
        {
            Stop();
        }
          // Move++;

            TMR2=0;

    }
	IFS0bits.T2IF = 0; // Reset interrupt flag
        return;
}

void Move_Forward(){
    LATDbits.LATD6=1; // direction of Motor 1 is opposite to Motor2
    LATDbits.LATD7=0; 
    OC2RS = 1000;
    OC3RS = 1000;
    return;   
}
void Move_Backward()
{
    LATDbits.LATD6=0;
    LATDbits.LATD7=1;
    OC2RS = 1000;
    OC3RS = 1000;
    return;
}
void Turn_Right()
{
    LATDbits.LATD6=1;
    LATDbits.LATD7=1;
    OC2RS = 1000;
    OC3RS = 1000;
    return;
}
void Turn_Left()
{
    LATDbits.LATD6=0;
    LATDbits.LATD7=0;
    OC2RS = 1000;
    OC3RS = 1000;
    return;
}
void Stop()
{    
    LATDbits.LATD1=0;
    LATDbits.LATD2=0;
    OC2RS = 0;
    OC3RS = 0;
    return;
}

