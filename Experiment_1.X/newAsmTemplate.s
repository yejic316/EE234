#include <p32xxxx.h>
.text  # the code is entered as a test
.set noreorder
.global main  # main is global that can be accessed by any function
.ent main  # enter the main 
main:                 # labels for the start of the main address
# Do something here
SetUPIOs:
    # 4 LEDs - pin RB10-13
	La $t0, TRISBCLR  
	ori $t1, $zero, 0x3C00
	SW $t1, 0($t0)
	
    # 2 Btns - pin RA4, RA7
	La $t0, TRISASET 
	ori $t1, $zero, 0x00C0  
	SW $t1, 0($t0)

	
WaitOnBtns:
            La $t0, PORTA
	    Lw $t1, 0($t0)
	    andi $t2, $t1,0x0040
	    BGTZ $t2, LEDON
	    Nop
	    andi $t2, $t1,0x0080
	    BGTZ $t2, LEDOFF
	    Nop
	    J WaitOnBtns
	    Nop
LEDON:
            La $t0, LATBSET
	    Ori $t1, $zero, 0x3C00
	    SW $t1, 0($t0)
	    J WaitOnBtns
	    Nop
LEDOFF:
	    La $t0, LATBCLR
	    Ori $t1, $zero, 0x3C00
	    SW $t1, 0($t0)
	    J WaitOnBtns
	    Nop

endless:
	j   endless
	nop 

.end main # used to end main

    





