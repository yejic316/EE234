// Lab #4
#include "Lab_4.h"

void main(){
    InitializeIO();
    InitializeTimer1();
    
    while(1){
        WaitOnBtn1(); 
        
        
      while(1){  
          BlinkingLEDs();
          if (PORTAbits.RA7 ==1){
              LATBCLR=0x3C00;
             break; 
          }
             ;
        
    }
    }
    return; 
}

void InitializeIO(){
    TRISAbits.TRISA6=1; // Btn1 as input
    TRISAbits.TRISA7=1; // Btn2 as input
    
    //LEDs 1-4 are outputs
    TRISBbits.TRISB10=0;
    TRISBbits.TRISB11=0;
    TRISBbits.TRISB12=0;
    TRISBbits.TRISB13 =0;
    
    LATBCLR = 0x3C00; // trun off all LEDs
    
    return ;
}
void InitializeTimer1(){
    T1CONbits.ON = 0; // turn off LED
    T1CONbits.TCKPS = 3; // prescale by 256 every 39062 tics is one second
    PR1 = 0xFFFF; 
    TMR1 = 0; 
    T1CONbits.ON = 1; // Starts Timer
    return ;
    
}
void WaitOnBtn1(){
    while (PORTAbits.RA6 == 0)
        ; // do nothing else exit the loop
     
    return; 
}

void BlinkingLEDs(){
   
    
     if  (TMR1>T4){ //LED4
        
         LATBbits.LATB13= !LATBbits.LATB13; 
         T4 +=9765;   
         count_T2+=1;
         count_T3+=1;
         
         if (count_T3 >=2)
         {
             LATBbits.LATB12= !LATBbits.LATB12; 

             count_T3=0;
         }         
         
         if (count_T2 >=3)
         {
             LATBbits.LATB11= !LATBbits.LATB11; 

             count_T2=0;
         }
    }
  
    if (TMR1> 39062){ // one second //LED1
          LATBbits.LATB10= !LATBbits.LATB10;
          T4 =9765;
          TMR1=0;


    }
  
}
