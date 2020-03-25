#include "Lab_7.h"

void main(){
     InitializeSystem();
     Interrupts_enable();
    while(1){
   
        ;
    }
    
    return; 
    
}
void  InitializeSystem(){
    Initialize_IO();
    Initialize_Timer1();
    Initialize_Timer2();
    Initialize_Timer3();
    Initialize_OC();
    Initialize_IC();
    InitializeADC();
}

void Initialize_IO(){
    // Motor Direction bits
    TRISDbits.TRISD6 =0;     
    TRISDbits.TRISD7 =0;     
    TRISDbits.TRISD1 =0;
    TRISDbits.TRISD2 =0;
    
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 =0;
    
    TRISBbits.TRISB1 = 0;
    LATBbits.LATB1 = 1;  // truns sonar on;
    
    //For LED1, LED2
    TRISBbits.TRISB10=0;
    TRISBbits.TRISB11=0;
    LATBbits.LATB10=0;
    LATBbits.LATB11=0;
    
    
}

void Initialize_Timer1(){
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 3;
    PR1 = 39062; // should be changed
    TMR1 = 0;
    T1CONbits.ON =1;       
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
void Initialize_Timer3(){
    T3CONbits.TON = 0;
    T3CONbits.TCKPS = 7;
    PR3 = 0xffffffff; // may want to change this value
    TMR3 = 0;
    T3CONbits.ON =1;       
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
void Initialize_IC(){
// Initialize IC2
    TRISDbits.TRISD9 = 1;
    IC2CON= 0x0000;
    IC2CONbits.SIDL = 1; // halt in CPU Idle Mode
    IC2CONbits.C32 = 0; // 16bit timer;
    IC2CONbits.ICTMR = 0; // select Timer 3;
    IC2CONbits.ICI = 1; // interrupt every 2 events
    IC2CONbits.ICM = 5; // increment every 16 rising edge
    
    
    // Initialize IC3
    TRISDbits.TRISD10 = 1;
    IC3CON= 0x0000;
    IC3CONbits.SIDL = 1; // halt in CPU Idle Mode
    IC3CONbits.C32 = 0; // 16bit timer;
    IC3CONbits.ICTMR = 0; // select Timer 3;
    IC3CONbits.ICI = 1; // interrupt every fourth event
    IC3CONbits.ICM = 5; // increment every 16 rising edge
    
    
}
void InitializeADC(){
        
    AD1CON1= 0x000000;
    AD1CON1bits.FORM = 0;// unsigned integer 10 bits 0 - 1024 = 0x2208;
    AD1CON1bits.SIDL = 1; // stop operation in the idle mode
    AD1CSSL = 0x0000;
    AD1CON1bits.ASAM = 1;//auto start sampling
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.SSRC =7;

    /* Configure ADC voltage referenceand buffer fill modes.VREF from AVDD and AVSS,Inputs are not scanned,Interrupt every sample */
    AD1CON2 = 0x0000;
    AD1CON2bits.VCFG = 7;  // Reference voltage to be Vdd & Vss;
    AD1CON2bits.OFFCAL = 0; // No Calibration 
    AD1CON2bits.SMPI = 1; //interrupt every other sampl
    // AD1CON3 Register
      AD1CON3= 0x0000;//Sample time = 2 TAD
      AD1CON3bits.ADCS = 8;  // Sample clock is 10MHz/16
      AD1CON3bits.SAMC = 2;  
  /* Configure ADC RB00 */
     AD1PCFG = 0xFFFE..; 
/* Configure input channels,CH0+ input is AN0.CHO- input is VREFL (AVss)  */                   
    AD1CHS = 0x0000;
    AD1CSSL = 0x0000;
    AD1CSSLbits.CSSL0 = 1;   
}

void Interrupts_enable(){
    //Interrupt for ADC
    IPC6bits.AD1IP = 7;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;   
    AD1CON1bits.ADON = 1;  

    // Interrupt for IC2
    IFS0bits.IC2IF =0;
    IPC2bits.IC2IP = 4;
    IEC0bits.IC2IE = 1;
    
    //// Interrupt for IC3
    IFS0bits.IC3IF =0;
    IPC3bits.IC3IP = 5;
    IEC0bits.IC3IE = 1;
    
      // turn ON IC2 & IC3
    IC2CONbits.ON = 1;
    IC3CONbits.ON= 1;
    
     //// Interrupt for Timer1
    IFS0bits.T1IF =0;
    IPC1bits.T1IP = 7;
    IEC0bits.T1IE = 1;
      
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
}

void __ISR(_INPUT_CAPTURE_2_VECTOR, IPL4SRS) IC2Interrupt(void){
    if (mode ==Forward){
 //   IC2CONbits.ON = 1;
        // Timer3 is stored on the upper 16bits of IC2BUF. So shift it by 16 bit
        unsigned int a = IC2BUF>>16;  // shift is used to read from Timer 3
        unsigned int b = IC2BUF>>16;  
        unsigned int c = IC2BUF;
        c = IC2BUF;
        c = IC2BUF;
        
        
        unsigned int f;
        if (a<b)
            f= b-a;
        else        //Check if Timer 3 is reset. 

            f=b+(65536)-a;
        speed1 = f;
         unsigned int f1 = speed1;  
        
    }
    else{ // empty the buffer. 
         unsigned int c = IC2BUF;
                c = IC2BUF;
                 c = IC2BUF;
                  c = IC2BUF;
                   c = IC2BUF;
     }
    
	IFS0bits.IC2IF = 0;
}
void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL5SRS) IC3Interrupt(void){
    
    if (mode == Forward){
        
       unsigned int a = IC3BUF>>16;  // shift is used to read from Timer 3
       unsigned int b = IC3BUF>>16;
       
        
       unsigned int f;
        if (a<b)
            f= b-a;
        else
            f=b+(65536)-a;
        speed2 = f;
        Check_Speed();
    }
    
    else{ // empty the buffer. 
         unsigned int c = IC3BUF;
        c = IC3BUF;
        c = IC3BUF;
        c = IC3BUF;
        c = IC3BUF;
    }
        
    
    IFS0bits.IC3IF = 0;
}


 void __ISR (_ADC_VECTOR, IPL7SRS) ADCInterrupt(void){
	
	//MotorForward();
    ReadADC();
	// Reset interrupt flag
	IFS1bits.AD1IF = 0;   
}
  
 void ReadADC(){
 unsigned int ADCValue = 0;//clear value
    int count =0;  
    AD1CON1bits.ASAM = 1;//auto start sampling
                                //for 31 TAD, and then go to conversion
    while (!AD1CON1bits.DONE)
                ;//conversion done?
               // AD1CON1bits.ASAM = 0;//yes, stop sample/convert
    for (count = 0; count <8; count++){//Reads the entire buffer
        ADCValue = ADCValue + ADC1BUF0;    
    }
    ADCValue = ADCValue >>3; // divide by 8 using a shift operation
    if (mode == Forward){
        if (ADCValue < 0x10){  // can be adjusted for the distance. 
            mode =Stop1;
            Stop();  // take action ( stop) move back turn    
        }
        else{
            Motor_Forward();
        }   
    }
    else if (mode==Turn){
        if (ADCValue > 0x20){
                mode =Stop3;
                Stop();  
    }
    }  
}
 
void Motor_Forward(){
        LATDbits.LATD6 = 0; 
        LATDbits.LATD7 = 1;  
            OC2RS = 1000;
        OC3RS = 1000;
	Check_Speed();
}
void Stop(){
    LATDbits.LATD1=0;
    LATDbits.LATD2=0;
    OC2RS = 0;
    OC3RS = 0;
}
void Turning(){
    
    LATDbits.LATD6=1;
    LATDbits.LATD7=1;
    OC2RS = 1000;
    OC3RS = 1000;
}
void Motor_Backward(){
 
        LATDbits.LATD6 = 1; 
        LATDbits.LATD7 = 0; 
          OC2RS = 500;
          OC3RS = 500;
}
void Check_Speed(){
    // Enter the algorithm for check speed. 
    // You should have speed1 & speed2, must use those values to adjust 
    //OC2RS & OC3RS.

    if(speed1>speed2)// Left>Right
    {
        
        LATBbits.LATB10=0;
        LATBbits.LATB11=1;

        OC2RS = OC2RS - 10;
        OC3RS =  OC3RS + 10;
        
    }    
    else// Left <= Right
    {    
        LATBbits.LATB10=1;
        LATBbits.LATB11=0;
        OC2RS = OC2RS + 10;
        OC3RS =  OC3RS - 10;
    }

}
 
void __ISR (_TIMER_1_VECTOR, IPL7SOFT) T1Interrupt(void){
	    // Navigate through the steps for finding the 
    if (mode==Stop1){
            TMR1=0;
            mode = Backward;
            Stop();

    }
    else if (mode==Backward){
        // enter code
            TMR1=0;
            mode = Stop2;
            Motor_Backward();
    }
    else if (mode==Stop2){
        // enter code
            TMR1=0;
            mode = Turn;
            Stop();
    }
    else if (mode==Turn){
        // enter code
            TMR1=0;
            mode = Stop3;
            Turning();
    }
    else if (mode == Stop3){
            TMR1=0;
            Stop();
            mode=Forward;
            Motor_Forward();

    }
	IFS0bits.T1IF =  0;
}

