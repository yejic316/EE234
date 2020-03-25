#include <p32xxxx.h>
.text  # the code is entered as a test
.set noreorder
.global main  # main i
     
     
.ent main  # enter the main 
     main: 
	JAL InitializeTimer1   # Jump and Link (JAL) will store the next instruction address in $ra
	Nop		# wait on the instruction when it is executed. 
    Initial_IO:
	JAL InitializeIO   	# Jump and Link (JAL) will store the next instruction address in $ra
	Nop		# wait on the instruction when it is executed. 
     WaitOnButton1:
	JAL WaitOnBtn1
	Nop
  LED1ON:
	JAL LED1
	Nop
      JAL Delay
	Nop

    LED2ON:
	JAL LED2
	Nop
     JAL Delay
	Nop
    LED3ON:
	JAL LED3
	Nop
     JAL Delay
	Nop
   LED4ON:
	JAL LED4
	Nop
     JAL Delay
	Nop
    
endless:
	J  LED1ON
	Nop
		
.end main # used to end main

.ent InitializeTimer1  
      InitializeTimer1:
	La $t0, T1CON                      	# Load the address of T1CON 
	Sw $zero, 0($t0)                   	# Store zeros in T1CON.  For initialization
	La $t0, TMR1                     	# Load the address of TMR1 
	Sw $zero, 0($t0)                   	# Store zeros in TMR1.  For initialized to zero
	La $t0, PR1                     	# Load the address of PR1 
	Ori $t1, $zero, 0xffff         	# Load the value 0xffff into register $t1
	Sw $t1, 0($t0)                   	# Store zeros in PR1.  For initialized to zero	
	La $t0, T1CONSET              	# Load the address of T1CONSET into $t0
	Ori $t1, $zero, 0x8030       	# 0x8030 corresponds to turn ON and pre-scale by 256
	Sw $t1, 0($t0)                     	# Store $t1 into T1CONSEt
	Jr    $ra                                	# Jump to return address $ra. The return address is updated when this 					# function is called. 
	nop 			# if the jump is executed, it will skip the next operation. Add nop after jr.
.end InitializeTimer1 

.ent InitializeIO
    InitializeIO:
	# Enter your code here
  	La $t0,TRISASET	    # configure Btn1, Btn2 (RA6, RA7)
	Ori $t1, $zero, 0x00c0
	Sw $t1, 0($t0)
	
  	La $t0,TRISBCLR	    # configure 4LEDs (RB10 - 13)
	Ori $t1, $zero, 0x3c00
	Sw $t1, 0($t0)	
	
	La $t0, LATBCLR	    # Turn off all LEDs at first
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)

.end InitializeIO

.ent WaitOnBtn1
     WaitOnBtn1:
	# Enter you code here
	La $t0, PORTA
	Lw $t1, 0($t0)
	andi $t2, $t1,0x0040
	BGTZ $t2, LED1ON
	nop	
	J WaitOnBtn1
	Nop
	

.end WaitOnBtn1

.ent LED1
     LED1:
	La $t0, LATBCLR
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	
	# Turn ON LED1
	La $t0, LATBSET
	Ori $t1, $zero, 0x0400
	SW $t1, 0($t0)
	
	# Reset TMR1 to zero
	La $t0, TMR1
	SW $zero, 0($t0)  # set TMR1 to zero
	# return
	Jr $ra
	Nop
.end LED1
.ent LED2
     LED2:
	La $t0, LATBCLR
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	
	# Turn ON LED2
	La $t0, LATBSET
	Ori $t1, $zero, 0x0800
	SW $t1, 0($t0)
	
	# Reset TMR1 to zero
	La $t0, TMR1
	SW $zero, 0($t0)  # set TMR1 to zero
	# return
	Jr $ra
	Nop
.end LED2	
.ent LED3
     LED3:
	# Enter your code here
	La $t0, LATBCLR
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	
	# Turn ON LED3
	La $t0, LATBSET
	Ori $t1, $zero, 0x1000
	SW $t1, 0($t0)
	
	# Reset TMR1 to zero
	La $t0, TMR1
	SW $zero, 0($t0)  # set TMR1 to zero
	# return
	Jr $ra
	Nop
.end LED3	
.ent LED4
     LED4:
	# Enter your code here
	La $t0, LATBCLR
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	
	# Turn ON LED4
	La $t0, LATBSET
	Ori $t1, $zero, 0x2000
	SW $t1, 0($t0)
	
	# Reset TMR1 to zero
	La $t0, TMR1
	SW $zero, 0($t0)  # set TMR1 to zero
	# return
	Jr $ra
	Nop

.end LED4	
.ent ClearLEDs
      ClearLEDs:
# clear all LEDs
        La $t0, LATBCLR
	Ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	Jr  $ra
	Nop
.end ClearLEDs

.ent Delay
Delay:
	# check if the btn2 is puah
	La $t0, PORTA
	Lw $t1, 0($t0)
	andi $t2, $t1,0x0080
	BGTZ $t2, Initial_IO
	nop
	
	# Read TMR1 and compare it for 2 seconds
	La $t0, TMR1
	LW $t1, 0($t0)
 	SLTI $t2, $t1, 1000   # 0.5 sec
	Nop
	
	# go back to delay if it less than X tics
	BGTZ $t2, Delay
	Nop
	
	# return if the X tics are acheived 
	Jr  $ra
	Nop


.end Delay
	