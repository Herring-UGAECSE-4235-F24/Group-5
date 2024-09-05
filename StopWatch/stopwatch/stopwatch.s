@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.global main
    	.func main


main:
	ldr r10 , =hundredths 
	ldr r11 , =seconds
	ldr r12 , =minutes
	mov r7, #0 @hundredth of a second count when hits 12,000 reset to 0 (aka hit 2 mins)
	mov r8, #0 @seconds
	mov r9, #0 @minutes
	str r7 , [r10] @using zero reg to reset
	str r8 , [r11]
	str r9 , [r12]

	
	
_reload:
	ldr r3, =10000000 @whatever time is a hunredth of a sec based on #of instructions since 1 inst per clock
	add r7, r7, #1 @increments every hundreth of a second
	str r7, [r10] @strs back to hundreths .data
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
		NOP
		NOP
		BL _colon
		@prints seconds
		NOP
		NOP
		LDR R0, =string         @ seed printf
    	LDR R1, =seconds
    	LDR R1, [R1]            @ seed printf
    	BL printf
		@prints colon
		NOP
		NOP
		BL _colon
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
	str R7, [R10] 		@hundreths is reset to 0 in mem
	add R8, R8, #1
	str R8, [R11]		@seconds is incremented in mem
	cmp R8, #60			@if 60 secs increment min
	beq _incrementMin
	bne _printloop
_incrementMin:
	add R9, R9, #1
	str R9, [R12] 		@increments min in mem
	mov R8,	#0 			@resets seconds to zero in mem
	str R8, [R11]		
	b _printloop
	
_colon:
	mov     R0, #1          @ 1 = StdOut
   	ldr     R1, =colon 		@sting to print
    mov     R2, #1         @length of out string
   	mov     R7, #4          @linux write system call
    svc     0               @call linux to print
	bx 		lr


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
