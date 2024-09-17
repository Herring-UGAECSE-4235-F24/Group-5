@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.global main
    .func main



main:
	b _clear

checkScan:
	ldr r1, =char                   @loads address of returned char back into r1
	ldrb r1, [r1]
    	cmp r1, #'r' 
	beq _run
	cmp r1, #'c'
	beq _clear 
	cmp r1, #'l'
	beq _lap
	cmp r1, #'s'
	beq _stop
	bx lr
display_time:
	LDR R0, =string         @ seed printf
        LDR R1, =minutes 
        LDR R2, =seconds		@ loads mins into R1 for print
        LDR R3, =hundredths
        LDR R1, [R1]            @ seed printf
        LDR R2, [R2]            @ seed printf
        LDR R3, [R3]            @ seed printf
        BL printf


_reload:
	ldr r3, =6000000 @whatever time is a hunredth of a sec based on delay loop 
	add r7, r7, #1 @increments every hundreth of a second
	ldr r4, =hundredths
	str r7, [r4] @strs back to hundreths .data
	cmp r7, #100
	BEQ _incrementSec
	
_delayloop:
	bl checkScan
	subs r3, r3, #1
	bne  _delayloop
	ldr r1, =Lap
	ldr r1, [r1]
	cmp r1, #0
	bleq display_time
	
_incrementSec:
	mov R7, #0
	ldr r4, =hundredths
	str R7, [R4] 		@hundreths is reset to 0 in mem
	add R8, R8, #1
	ldr r5, =seconds
	str R8, [R5]		@seconds is incremented in mem
	cmp R8, #60			@if 60 secs increment min
	beq _incrementMin
	b _reload
_incrementMin:
	mov R8,	#0 			@resets seconds to zero in mem
	str R8, [R5]
	add R9, R9, #1
	ldr r6, =minutes
	str R9, [R6] 		@increments min in mem		
	
	ldr r1, =Lap
	ldr r1, [r1]
	cmp r1, #0
	bleq display_time
	b _reload


_stop:
	@if stop using blocking of scanf 
		bl block
	ldr r0, =format
    ldr r1, =char
    Bl scanf				@keyblock on so it waits for input to start
	ldr r1, =char                   @loads address of returned char back into r1
    ldrb r1, [r1]
    cmp r1, #'r' 
	beq _run
	cmp r1, #'c'
	beq _clear
	b _stop
	@if scan f returns r continue from previous state
	@if L do nothing
	@if C reset
_lap:
	@stop printing but count is running in the background still
		bl deblock
	mov r1, #1
	ldr r2, =Lap
	str r1, [r2]  @used to check if lap or just run to decide if we need to display or not

	ldr r0, =format
    ldr r1, =char
    Bl scanf
	b _reload

	@if scanf retuns L nothing
	@if scanf returns r continue count from backgrounf running time
	@if scanf returns c clear count and 
_clear:
	mov r0, #0
        bl E4235_KYBdeblock     
        

	ldr r4 , =hundredths 
	ldr r5 , =seconds
	ldr r6 , =minutes
	mov r7, #0 @hundredth of a second count when hits 12,000 reset to 0 (aka hit 2 mins)
	mov r8, #0 @seconds
	mov r9, #0 @minutes
	str r7, [r4] @using zero reg to reset
	str r8, [r5]
	str r9, [r6]

	LDR R0, =string         @ seed printf
        LDR R1, =minutes 
        LDR R2, =seconds                @ loads mins into R1 for print
        LDR R3, =hundredths
        LDR R1, [R1]            @ seed printf
        LDR R2, [R2]            @ seed printf
        LDR R3, [R3]            @ seed printf
        BL printf
        
						@turn keyblock on to wait for scanf
    	ldr r0, =format
    	ldr r1, =char
    	Bl scanf				@keyblock on so it waits for input to start
    	ldr r1, =char                   @loads address of returned char back into r1
    	ldrb r1, [r1]
    	cmp r1, #'r' 
	bne _clear
    

_run:
	
	 mov r0, #1    @sets deblock to 1
	 bl E4235_KYBdeblock

	mov r1, #0
	ldr r2, =Lap
	str r1, [r2]  @used to check if lap or just run to display
	ldr r0, =format
	ldr r1, =char
	mov r2, #0
	strb r2, [r1]
    	bl scanf
	ldr r1, =char                   @loads address of returned char back into r1
        ldrb r1, [r1]
        cmp r1, #'c' 
	beq exit
	b _reload


_exit:
	mov     R0, #0          @use 0 return code
	mov R7, #1          @service command code 1 
	svc     0               @call linux to terminate

deblock:
    mov r0, #1    @sets deblock to 1
    bl E4235_KYBdeblock
    bx lr
block:
	mov r0, #0
	bl E4235_KYBdeblock	
	bx lr

.data
char:
		.byte  0
string:
       	        .asciz "%02d:%02d:%02d\n"
format:
		.asciz " %c"			 	@for reading char	
hundredths:
	        .word   0               @ hundreths count storage for printing
seconds:
		.word 	0 				@ seconds count storage for print
minutes:
		.word	0				@ minutes count for print
Lap:
		.word   0
