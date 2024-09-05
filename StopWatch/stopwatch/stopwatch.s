@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.global main
    .func main


main:
	ldr r4 , =hundredths 
	ldr r5 , =seconds
	ldr r6 , =minutes
	mov r7, #0 @hundredth of a second count when hits 12,000 reset to 0 (aka hit 2 mins)
	mov r8, #0 @seconds
	mov r9, #0 @minutes
	str r7, [r4] @using zero reg to reset
	str r8, [r5]
	str r9, [r6]

	
	
_reload:
	ldr r3, =9020000 @whatever time is a hunredth of a sec based on delay loop 
	add r7, r7, #1 @increments every hundreth of a second
	str r7, [r4] @strs back to hundreths .data
	cmp r7, #100
	BEQ _incrementSec
	
_delayloop:
	subs r3, r3, #1
	bne  _delayloop
	
_printloop:
	@Prints mins
    	LDR R0, =string         @ seed printf
    	LDR R1, =minutes 		@ loads mins into R1 for print
    	LDR R1, [R1]            @ seed printf
    	BL printf
		@prints colon
		LDR R0, =colon
		BL printf
		@prints seconds
		LDR R0, =string         @ seed printf
    	LDR R1, =seconds
    	LDR R1, [R1]            @ seed printf
    	BL printf
		@prints colon
		LDR R0, =colon
		BL printf
		@prints hundreths and new line
		LDR R0, =laststring         @ seed printf
    	LDR R1, =hundredths
    	LDR R1, [R1]            @ seed printf
    	BL printf


		cmp R9, #2
		beq _exit @if 2:00:00 is printed reset to 0:0:0

   	B _reload @else countnue incrementing hundreths

_incrementSec:
	mov R7, #0
	str R7, [R4] 		@hundreths is reset to 0 in mem
	add R8, R8, #1
	str R8, [R5]		@seconds is incremented in mem
	cmp R8, #60			@if 60 secs increment min
	beq _incrementMin
	bne _printloop
_incrementMin:
	mov R8,	#0 			@resets seconds to zero in mem
	str R8, [R5]
	add R9, R9, #1
	str R9, [R6] 		@increments min in mem		
	b _printloop
	

_exit:
	mov     R0, #0          @use 0 return code
	mov     R7, #1          @service command code 1 
	svc     0               @call linux to terminate

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
