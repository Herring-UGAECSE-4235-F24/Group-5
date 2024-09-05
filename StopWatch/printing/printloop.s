/* Attempting to output loop counter with printf */

        .global main
        .func main

main:
        PUSH {LR}
        BAL _loop

_printloop:
	@Prints mins
    	LDR R0, =string         @ seed printf
    	LDR R1, =minutes 		@ loads mins into R1 for print
    	LDR R1, [R1]            @ seed printf
    	BL printf
	@prints colon
	BL colon
	@prints seconds
	LDR R0, =string         @ seed printf
    	LDR R1, =seconds
    	LDR R1, [R1]            @ seed printf
    	BL printf
	@prints colon
	BL colon
	@prints hundreths and new line
	LDR R0, =laststring         @ seed printf
    	LDR R1, =hundredths
    	LDR R1, [R1]            @ seed printf
    	BL printf
	cmp R9, #2
	beq _exit @if 2:00:00 is printed reset to 0:0:0
_exit:
        POP {PC}
        MOV PC, LR

.data
colon:
		.asciz ":"
string:
       		.asciz "%d"
laststring:
		.asciz "%d\n"
hundredths:
	        .word   0               @ hundreths count storage for printing
seconds:
		.word 	0 				@ seconds count storage for print
minutes:
		.word	0				@ minutes count for print

