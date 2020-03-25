#include <p32xxxx.h>

    .global main    
 
    .data
    .text
  
    .ent main
    main:
	
	jal InitializeIO
	nop	
	jal InitializeTimer2
	nop	
	jal InitializeOC
	nop
	jal WaitOnBtn
	nop

    start:
    	La $t0, PORTG
	lw $t1, 0($t0)
	andi $s7, $t1,0xf000
	xori $t2, $s7, 0xe000 # 1110 check if sensor4 is 0 	
	BEQZ  $t2, RRIGHT # RIGHT
	nop
	
	xori $t2, $s7, 0xc000 # 1100   	
	BEQZ  $t2, TURNRIGHT # RRIGHT	
	nop

	xori $t2, $s7, 0x8000 # 1000	
	BEQZ  $t2, TURNRIGHT	
	nop

	xori $t2, $s7, 0xd000 # 1101 	
	BEQZ $t2, RIGHT # MoveForward
	nop

	xori $t2, $s7, 0x9000# 1001 
	BEQZ $t2, MoveForward	
	nop

	xori $t2, $s7, 0xb000# 1011  	
	BEQZ $t2,  LEFT # MoveForward	
	nop

	xori $t2, $s7, 0x7000 # 0111
	BEQZ $t2, LLEFT # LEFT
	nop

	xori $t2, $s7, 0x6000 # 0110
	BEQZ $t2, MoveForward
	nop	
	
	# La $s1, PORTG
	xori $t2, $s7, 0x0000
	BEQZ $t2, MoveForward
	nop
	xori $t2, $s7, 0x3000 # 0011 
	BEQZ $t2, TURNLEFT # LLEFT
	nop

	xori $t2, $s7, 0x1000 # 0001 
	BEQZ $t2, TURNLEFT
	nop	

	# additional....
	xori $t2, $s7, 0x5000 # 0101
	BEQZ $t2, MoveForward
	nop
	xori $t2, $s7, 0xa000 # 1010
	BEQZ $t2, MoveForward
	nop
	
	xori $t2, $s7, 0x4000 # 0100
	BEQZ $t2, RIGHT
	nop

	xori $t2, $s7, 0x2000 # 0010
	BEQZ $t2, LEFT
	nop	
		
	j start
	nop
	
    .end main
   

.ent InitializeIO
	InitializeIO:
	# use LEDs as indicators
	la $t0, TRISBCLR	# configure 4LEDs as output
	ori $t1,$zero, 0x3C00	
	sw $t1, 0($t0)
	
	la $t0, LATBCLR		# turn off 4 LEDs
	ori $t1,$zero, 0x3C00
	sw $t1, 0($t0)
	
    # buttons
	La $t0,TRISASET	    # configure Btn1 (RA6)
	Ori $t1, $zero, 0x0040
	Sw $t1, 0($t0)
	
    # motors
	la $t0, TRISDCLR	# configure motor as output(RD6, RDD7, RD1, RD2)
	ori $t1,$zero, 0x00c6	
	sw $t1, 0($t0)	
	
	la $t0, LATDCLR		
	ori $t1,$zero, 0x0006	# RD1, RD2
	sw $t1, 0($t0)
	
	# LS sensor
	La $t0,TRISGSET	    # configure (RG0- RG3) as input
	Ori $t1, $zero, 0xf000
	Sw $t1, 0($t0)
	
	
	jr $ra
	nop
	   
    .end InitializeIO 
    
    
.ent InitializeTimer2
	InitializeTimer2:
	
	La $t0, T2CON                      	
	Sw $zero, 0($t0)                   	
	La $t0, TMR2                     	
	Sw $zero, 0($t0)                   	
	La $t0, PR2                     	
	li $t1, 3500    
	Sw $t1, 0($t0) 
	
	La $t0, T2CONSET              	
	li $t1, 0x0030       	# bit 6:4 is 011 - prescale by 8
	ori $t1, $t1, 0x8000	# bit  15 is 1 - Turn On Timer2
	Sw $t1, 0($t0)                     
	Jr    $ra                          
	nop 
	
.end InitializeTimer2
    
.ent InitializeOC
	InitializeOC:
    
   	la $t0, OC2CON
	Li $t1, 0x0000	# initialize all bits
	sw $t1, 0($t0)
	
  	la $t0, OC3CON
	Li $t1, 0x0000	# initialize all bits
	sw $t1, 0($t0)
      	    
    
    # for OC2
	la $t0, OC2R	    
	li $t1, 0
	sw $t1, 0($t0)
	
	la $t0, OC2RS
	li $t1, 0
	sw $t1, 0($t0)	
    
	la $t0, OC2CON
	Li $t1, 6		# bit 2:0 is 110 - PWM mode
	ori $t1, $t1, 0x8000	# bit 15 is 1 - Turn On OC2 module
	sw $t1, 0($t0)		# bit 3 is 0 - Timer2 clk src / bit 5 is 0 - 16bit timer
	
    # for OC3
	la $t0, OC3R	    
	li $t1, 0
	sw $t1, 0($t0)
	
	la $t0, OC3RS
	li $t1, 0
	sw $t1, 0($t0)	
    
	la $t0, OC3CON
	Li $t1, 6		# bit 2:0 is 110 - PWM mode
	ori $t1, $t1, 0x8000	# bit 15 is 1 - Turn On OC3 module
	sw $t1, 0($t0)		# bit 3 is 0 - Timer2 clk src / bit 5 is 0 - 16bit timer
	
	Jr    $ra                          
	nop 
	
.end InitializeOC

.ent WaitOnBtn
    WaitOnBtn:

	La $t0, PORTA
	Lw $t1, 0($t0)
	andi $t2, $t1,0x0040	# RA6 - Btn1
	BGTZ $t2, main
	nop	
	J WaitOnBtn
	Nop	
	
.end WaitOnBtn
     
.ent MoveForward
	MoveForward:
    
    	la $t0, LATDSET # direction of motor 
	li $t1, 0x0080	# bit 7 is 1 for OC3
	sw $t1, 0($t0)
	
	la $t0, LATDCLR # direction of motor 
	li $t1, 0x0040	# bit 6 is 0 for OC2se
	sw $t1, 0($t0)
	
	la $t0, OC2RS
	li $t1, 800
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 800
	sw $t1, 0($t0)
	
	jr $ra
	nop

.end MoveForward
.ent TURNLEFT
	TURNLEFT:
    	
	la $t0, LATDCLR # direction of motor 
	li $t1, 0x00c0	# bit 7 is 0 for OC3
	sw $t1, 0($t0)
	
	la $t0, OC2RS
	li $t1, 800
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 800
	sw $t1, 0($t0)	

	jr $ra
	nop
.end TURNLEFT	    
.ent LLEFT
	LLEFT:
	
	la $t0, LATDCLR # direction of motor 
	li $t1, 0x00c0	# bit 7 is 0 for OC3
	sw $t1, 0($t0)
	
	sw $t1, 0($t0)
	la $t0, OC2RS
	li $t1, 200
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 700
	sw $t1, 0($t0)	
	 
	jr $ra
	nop


.end LLEFT
.ent LEFT
	LEFT:
    
    
    	la $t0, LATDSET # direction of motor 
	li $t1, 0x0080	# bit 6 is 1 for OC2
	sw $t1, 0($t0)
	
	la $t0, LATDCLR # direction of motor 
	li $t1, 0x0040	# bit 7 is 0 for OC3
	sw $t1, 0($t0)
	
	la $t0, OC2RS
	li $t1, 600
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 700
	sw $t1, 0($t0)	


	jr $ra
	nop


.end LEFT
.ent RIGHT
	RIGHT:
	la $t0, LATDSET # direction of motor 
	li $t1, 0x0080	# bit 6 is 1 for OC2
	sw $t1, 0($t0)
	
	la $t0, LATDCLR # direction of motor 
	li $t1, 0x0040	# bit 7 is 0 for OC3
	sw $t1, 0($t0)
	
	la $t0, OC2RS
	li $t1, 700
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 600
	sw $t1, 0($t0)
	
 	jr $ra
	nop
.end RIGHT

.ent RRIGHT
	RRIGHT:
    		la $t0, LATDSET # direction of motor 
	li $t1, 0x00c0	# bit 7 is 0 for OC3
	sw $t1, 0($t0)

	
    	la $t0, OC2RS
	li $t1, 700
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 200
	sw $t1, 0($t0)	

	jr $ra
	nop
.end RRIGHT
.ent TURNRIGHT
	TURNRIGHT:

	la $t0, LATDSET # direction of motor 
	li $t1, 0x00c0	# bit 7 is 0 for OC3
	sw $t1, 0($t0)
    	la $t0, OC2RS
	li $t1, 700
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 700
	sw $t1, 0($t0)	
	
	jr $ra
	nop
.end TURNRIGHT	
	
.ent NoLine
    NoLine:
    
	la $t0, OC2RS
	li $t1, 0
	sw $t1, 0($t0)			
	
	la $t0, OC3RS
	li $t1, 0
	sw $t1, 0($t0)	
	
	la $t0, LATDCLR
	li $t1, 0x0003 # LATD1 and LATD2 
	sw $t1, 0($t0)
	jr $ra
	

.end NoLine

