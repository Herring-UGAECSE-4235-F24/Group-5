@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.global main
    .func main


main:
	
	ldr r1, =108 (minutes)


l1:
	ldr	r2, =1000000	@  (seconds loop count) 
l2:	
	ldr	r3, =1000000	@  (hundreds loop count) 
l3:
	
	subs	r3, r3, #1
	cmp 	r3 MOD #10000, 0
	bleq _PrintloopH
	bne l3
	subs    r2, r2, #1              @ r2 = r2 – 1, decrement r2 (i) 
	cmp 	r2 MOD #16666, 0
	bleq _PrintloopS
	bne	l2			@ repeat it until r1 = 0 
	subs	r1, r1, #1		@ r2 = r2 – 1, decrement r2 (outer loop) 
	cmp 	r2 MOD #54, 0
	bleq _PrintloopM
	bne	l1			@ repeat it until r2 = 0 


_PrintloopH:
        LDR R0, =string         @ seed printf
        LDR R1, =hundredths
        LDR R1, [R1]            @ seed printf
        BL printf

        LDR R1, =hundredths
        LDR R1, [R1]
        ADDS R1, #0x1
        LDR R2, =hundredths
        STR R1, [R2]            @ write back
		cmp R2, #100
		LDREQ 0, [hundredths]
        BEQ _PrintloopS
        Bx LR
_PrintloopS:
        LDR R0, =string         @ seed printf
        LDR R1, =seconds
        LDR R1, [R1]            @ seed printf
        BL printf

        LDR R1, =seconds
        LDR R1, [R1]
        ADDS R1, #0x1
        LDR R2, =seconds
        STR R1, [R2]            @ write back
		cmp R2, #60
		LDREQ 0, [seconds]
        BEQ _PrintloopM
        Bx LR
_PrintloopM:
        LDR R0, =string         @ seed printf
        LDR R1, =minutes
        LDR R1, [R1]            @ seed printf
        BL printf

        LDR R1, =minutes
        LDR R1, [R1]
        ADDS R1, #0x1
        LDR R2, =minutes
        STR R1, [R2]            @ write back
		cmp R2, #2
		LDREQ 0, [minutes]
        BEQ _reset
        Bx LR
_reset:
	STR 0, [hundredths]
	STR 0, [seconds]
	STR 0, [minutes]
_exit:
	@ terminate the program
	mov   	r7, #1
	svc   0

.data
string:
	 .asciz "%d\n"
hundredths:
        .word 0
seconds:
		.word 0
minutes: 
		.word 0



