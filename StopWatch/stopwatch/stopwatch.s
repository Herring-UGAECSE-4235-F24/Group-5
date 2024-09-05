@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.global main
    .func main


main:
	mov r7, #0 @hundredth of a second count when hits 12,000 reset to 0 (aka hit 2 mins)
	mov r8, #0 @seconds
	mov r9, #0 @minutes
	str #0, [hundredths]
	str #0, [seconds]
	str #0, [minutes]
	
_reload:
	ldr r3, #100000 @whatever time is a hunredth of a sec based on #of instructions since 1 inst per clock
	add r4, r4, #1 @increments every hundreth of a second
	str r4, [hundredths]
	cmp r4, 100
	BEQ _incrementSec
_delayloop:
	subs r3, r3, #1
_printloop:
	@Prints mins
    LDR R0, =string         @ seed printf
    LDR R1, =minutes
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
	LDR R0, =laststringstring         @ seed printf
    LDR R1, =hundredths
    LDR R1, [R1]            @ seed printf
    BL printf
	cmp R9, #2
	beq main @if 2:00:00 is printed reset to 0:0:0

    B _reload @else countnue incrementing hundreths

_incrementSec:
	mov R7, #0
	str R7, [hundredths]
	add R8, R8, #1
	str R8, [seconds]
	cmp R8, #60
	beq _incrementMin
	bne _printloop
_incrementMin:
	add R9, R9, #1
	str R9, [minutes]
	mov R8,	#0 @resets seconds to zero
	str R8, [seconds]
	b _printloop
	
_colon:
	mov     R0, #1          @ 1 = StdOut
    ldr     R1, =colon 		@sting to print
    mov     R2, #1         @length of out string
    mov     R7, #4          @linux write system call
    svc     0               @call linux to print


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