#include <xc.h> 
    .text
    .set noreorder
    .global main
    
    .ent main
    main:
	jal InitializeTimer1
	nop
	
	jal InitializeTimer2
	nop
	
	jal InitializeAudioIO
	nop
	
	jal InitializeBtn
	nop
	
	jal WaitOnBtn1
	nop
	
	j Play
	nop
	
	
    endless:
        j endless   
    .end main
   

.ent InitializeAudioIO
	InitializeAudioIO:
	# G port is used by Power Amp port 12, 13, 14, 15
	la $t0, TRISGCLR    # G port is set to 0 as output
	ori $t1,$zero, 0xF000
	sw $t1, 0($t0)
	
	la $t0, LATGSET
	ori $t1,$zero, 0xF000
	sw $t1, 0($t0)
	
	la $t0, LATGSET		
	ori $t1,$zero, 0xA000	# 1010 0000 0000 0000  port 13, 15
	sw $t1, 0($t0)
	
	
	# use LEDs as indicators
	la $t0, TRISBCLR	# configure 4LEDs as output
	ori $t1,$zero, 0x3C00	
	sw $t1, 0($t0)
	
	la $t0, LATBSET		# turn on 4 LEDs
	ori $t1,$zero, 0x3C00
	sw $t1, 0($t0)
	
	jr $ra
	nop
	   
    .end InitializeAudioIO 

# add all other necessary functions

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
	    Ori $t1, $zero, 0x8010       	# 0x8030 corresponds to turn ON and pre-scale by 256
	    Sw $t1, 0($t0)                     	# Store $t1 into T1CONSEt
	    Jr    $ra                                	# Jump to return address $ra. The return address is updated when this 					# function is called. 
	    nop 			# if the jump is executed, it will skip the next operation. Add nop after jr.
    .end InitializeTimer1
    
    .ent InitializeTimer2
	InitializeTimer2:
	    La $t0, T2CON                      	# Load the address of T2CON 
	    Sw $zero, 0($t0)                   	# Store zeros in T2CON.  For initialization
	    La $t0, TMR2                     	# Load the address of TMR2 
	    Sw $zero, 0($t0)                   	# Store zeros in TMR2.  For initialized to zero
	    La $t0, PR2                     	# Load the address of PR2 
	    Ori $t1, $zero, 0xffff         	# Load the value 0xffff into register $t1
	    Sw $t1, 0($t0)                   	# Store zeros in PR2.  For initialized to zero	
	    La $t0, T2CONSET              	# Load the address of T2CONSET into $t0
	    Ori $t1, $zero, 0x8030       	# 0x8030 corresponds to turn ON and pre-scale by 256
	    Sw $t1, 0($t0)                     	# Store $t1 into T2CONSEt
	    Jr    $ra                                	# Jump to return address $ra. The return address is updated when this 					# function is called. 
	    nop 			# if the jump is executed, it will skip the next operation. Add nop after jr.

    .end InitializeTimer2
    
    .ent InitializeBtn
	InitializeBtn:
	    La $t0,TRISASET	    # configure Btn1, Btn2 (RA6, RA7)
	    Ori $t1, $zero, 0x00c0
	    Sw $t1, 0($t0)
    
    .end InitializeBtn
    
    .ent WaitOnBtn1
	WaitOnBtn1:
    
     	    la $t0, LATBCLR  # will need to be clear LEDs pin
 	    li $t1, 0x3C00
 	    sw $t1, 0($t0)
 	    
	    La $t0, PORTA
	    Lw $t1, 0($t0)
	    andi $t2, $t1,0x0040
	    BGTZ $t2, Play
	    nop	
	    J WaitOnBtn1
	    Nop

    .end WaitOnBtn1
  .ent Play
   Play:
        # clear all LEDs
	la $t0, LATBCLR  # will need to be clear LEDs pin
	li $t1, 0x3C00
	sw $t1, 0($t0)
	
	la $t0, LATBSET  # will need to be changed to the LED pin
	li $t1, 0x0400
	sw $t1, 0($t0)
	
	# play Note1
        li $a0, 2000  # key time Timer2
	li $a1,	1000  # frequency Timer1
	jal Tone
	nop    
		
	# play Note2
        li $a0, 1000  # key time Timer2
	li $a1, 950  # frequency Timer1
	jal Tone
	nop

	# play Note3
        li $a0, 1000  # key time Timer2
	li $a1, 900  # frequency Timer1
	jal Tone
	nop   
	
        # play Note4
        li $a0, 1000  # key time Timer2
	li $a1, 950  # frequency Timer1
	jal Tone
	nop 
	
	# play Note5
        li $a0, 1000  # key time Timer2
	li $a1,	1000  # frequency Timer1
	jal Tone
	nop  
	
	# play Note6
        li $a0, 1000  # key time Timer2
	li $a1,	1000  # frequency Timer1
	jal Tone
	nop  
	
	# play Note7
        li $a0, 1000  # key time Timer2
	li $a1,	1000  # frequency Timer1
	jal Tone
	nop  
	
	# play Note8
        li $a0, 1000  # key time Timer2
	li $a1,	1100  # frequency Timer1
	jal Tone
	nop  
	
	# play Note9
        li $a0, 1000  # key time Timer2
	li $a1,	10500  # frequency Timer1
	jal Tone
	nop  	
	
	# clear all LEDs
	la $t0, LATBCLR  # will need to be clear LEDs pin
	li $t1, 0x3C00
	sw $t1, 0($t0)
	J Play	
    
    .end Play
    
    .ent Tone
      Tone:
	
	la $t0, LATGINV  
	li $t1, 0x1000
	sw $t1, 0($t0)
      Delay1:
    
    	# check if the btn2 is push
	La $t0, PORTA
	Lw $t1, 0($t0)
	andi $t2, $t1,0x0080
	BGTZ $t2, WaitOnBtn1
	nop
	
	la $t0, TMR1
	lw $t1, 0($t0)
	slt $t2, $t1,$a1
	nop
	bgtz $t2, Delay1
	nop
	
	sw $zero, 0($t0)  # intializes TMR1 to zero
	la $t0, LATGINV  # will need to be changed to the input pin
	li $t1, 0x1000
	sw $t1, 0($t0)
	
	
	la $t7, PORTA
        lw $t8, 0($t7)
	andi $t9, $t8, 0x0080
        bgtz $t9, main
	nop
	
	la $t0, TMR2
	lw $t1, 0($t0)
	slt $t3, $t1,$a0
	nop
	bgtz $t3, Delay1
	nop
	sw $zero, ($t0)	
    
	jr $ra
	nop
    
    .end Tone
    
    
   
