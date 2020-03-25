#include "Lab_8.h"
void main(){
   
    IO_Setup(); 
    Initialize_Timer2();
    Initialize_OC();

 //   Wait500ms();
    UART2_Setup(); 
   EnableInterrupt(); 
     
     // Turn On UART2
     U2MODEbits.ON = 1; 
      Wait500ms();
    while(1){
        if (PORTAbits.RA6==1)
        {
            Wait500ms();
            Wait500ms();
        }
    }
    return; 
}
void IO_Setup(){
    // LED IO bits
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    LEDsOFF();
    
    // Timer 1
     T1CON = 0; 
     TRISAbits.TRISA6 = 1;
     TRISAbits.TRISA7 = 1; 
    T1CONbits.TCKPS = 3;
    // U2 IO bits 
    TRISFbits.TRISF12 = 1; 
    TRISFbits.TRISF5= 0;
    TRISFbits.TRISF4 = 1;  
    TRISFbits.TRISF13 = 0;
    
    // for BT Module
    TRISEbits.TRISE8 = 1;
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 1; 
    
    // Motor Direction bits
    TRISDbits.TRISD6 =0;     
    TRISDbits.TRISD7 =0;     
    TRISDbits.TRISD1 =0;
    TRISDbits.TRISD2 =0;
    
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 =0;

    
    return ; 
}
void LEDsOFF(){
    LATBbits.LATB10 = 0; 
    LATBbits.LATB11 = 0; 
    LATBbits.LATB12 = 0; 
    LATBbits.LATB13 = 0; 
       return; 
}
void UART2_Setup(){
    U2MODE_Config();
    U2STAT_Config();
    U2INT_Config(); 
    return;
}


void U2MODE_Config(){
     U2MODE =0;  // default State
     U2MODEbits.UEN = 0; 
     U2MODEbits.ABAUD = 0;
    return; 
}
void U2STAT_Config(){
     
    // Enable Transmitter & Receiver
    U2STAbits.UTXEN = 0; 
    U2STAbits.URXEN = 1;   
    U2BRG = 5;
    return; 
}
void U2INT_Config(){
     // Interrupt config. for transmitting 
    
    IPC8bits.U2IP = 7;
    IPC8bits.U2IS = 3; 
    
    IFS1bits.U2TXIF = 0; 
    IEC1bits.U2TXIE = 0; 
  
    // Interrupt config. for receiving
    IFS1bits.U2RXIF = 0; 
    IEC1bits.U2RXIE= 1; 
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

void Initialize_OC(){
    
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
}




void Wait500ms(){
    
    TMR1 = 0; 
    PR1 = 0xFFFF; 
    T1CONbits.ON = 1;
    // wait for 500ms
    while(TMR1< 20000)
        ;
    
   
    TMR1 = 0; 
    T1CONbits.ON = 0;
    
}
void EnableInterrupt(){
    // timer 2 interrupt enable
    IFS0bits.T2IF =0;
    IPC2bits.T2IP = 7;
    IEC0bits.T2IE = 1;

    IFS1bits.U2EIF = 0;
    IPC8bits.U2IP = 6;
    IEC1bits.U2EIE = 1;
    
     INTCONbits.MVEC=1;
     __builtin_enable_interrupts();
		return;
}

void __ISR(_UART_2_VECTOR, IPL6SOFT)  UARTRX2Interrupt() {
    int a = U2BRG;
    if (IFS1bits.U2RXIF ==1){
        unsigned short data = U2RXREG;
        
        LEDsOFF(); 
        if (data == 0x91){
           LATBbits.LATB10 = 1;
            Dir = NW;  // Move NW
        }
        else if (data == 0x92){
            LATBbits.LATB11 = 1;
            Dir = N;  // Move N
        }
         else if (data == 0x93){
            LATBbits.LATB12 = 1;
            Dir = NE;  // Move NE
        }
         else if (data == 0x94){
            LATBbits.LATB13 = 1;
            Dir = W;  // Move W
        }
         else if (data == 0x95){
            Dir = STOP;  // Move Stop
        }
         else if (data == 0x96){
            LATBbits.LATB13 = 1;
            LATBbits.LATB12 = 1;
            Dir = E;  // Move E
        }
        else if (data == 0x97){
            LATBbits.LATB13 = 1;
            LATBbits.LATB11 = 1;
            Dir = SW;  // Move SW
        }
        else if (data == 0x98){
            LATBbits.LATB13 = 1;
            LATBbits.LATB10 = 1; 
            Dir = S;  // Move S
        }
        else if (data == 0x99){
            LATBbits.LATB13 = 1;
            LATBbits.LATB12 = 1;
            LATBbits.LATB11 = 1;   
            Dir = SE;  // Move SE
        }
    IFS1bits.U2RXIF = 0; 
    }
    return; 	
}


void __ISR (_TIMER_2_VECTOR, IPL7SRS)  T2Interrupt(void) 
{
    if(Dir == NW)
    {
        Move_NW();        
    }
    else if (Dir == N)
    {
        Move_N();
    }
    else if (Dir == NE)
    {
        Move_NE();
        
    }
    else if (Dir == W)
    {
        Move_W();
    }
    else if (Dir == E)
    {
        Move_E();        
    }    
    else if (Dir == SW)
    {
        Move_SW();        
    }
    else if (Dir == S)
    {
        Move_S();        
    }
    else if (Dir == SE)
    {
        Move_SE();
        
    }
    else
        Stop();
    TMR2=0;
    IFS0bits.T2IF =0;

}

void Stop()
{
    LATDbits.LATD1=0;
    LATDbits.LATD2=0;
    OC2RS = 0;
    OC3RS = 0;
    
}
void Move_NW()
{
    LATDbits.LATD6 = 0; 
    LATDbits.LATD7 = 1;  
    OC2RS = 700;
    OC3RS = 1200;
    
}
void Move_N()
{
    LATDbits.LATD6 = 0; 
    LATDbits.LATD7 = 1;  
    OC2RS = 1000;
    OC3RS = 1000;
    
}
void Move_NE()
{
    LATDbits.LATD6 = 0; 
    LATDbits.LATD7 = 1;  
    OC2RS = 1200;
    OC3RS = 700;
    
}
void Move_W()
{
    LATDbits.LATD6 = 0; 
    LATDbits.LATD7 = 0;  
    OC2RS = 1000;
    OC3RS = 1000;
    
}
void Move_E()
{
    LATDbits.LATD6 = 1; 
    LATDbits.LATD7 = 1;  
    OC2RS = 1000;
    OC3RS = 1000;
    
}
void Move_SW()
{
    LATDbits.LATD6 = 1; 
    LATDbits.LATD7 = 0;  
    OC2RS = 700;
    OC3RS = 1200;
    
}
void Move_S()
{
    LATDbits.LATD6 = 1; 
    LATDbits.LATD7 = 0;  
    OC2RS = 1000;
    OC3RS = 1000;
    
}
void Move_SE()
{
    LATDbits.LATD6 = 1; 
    LATDbits.LATD7 = 0;  
    OC2RS = 1200;
    OC3RS = 700;
    
}