@This is a delay program.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:00, the stopwatch should go back to 0:00:00 and keep running.  The display
@output should be as described.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.
	.data
	string: .asciz "%d\n"
	
	.text
	.global main
	.extern printf


main:
	

	LDR R0, =string
	LDR R1, =0xFFFF /*Output number*/
	BL printf
	B exit
	mov	r1, #108		@ (seconds loop count)
 

l1:
	ldr	r2, =1000000	@  (hundreds loop count) 
l2:	
	ldr	r3, =1000000	@  (mili loop count) 
l3:
	
	subs	r3, r3, #1
	bl ASCII
	bne l3
	subs    r2, r2, #1              @ r2 = r2 – 1, decrement r2 (i) 
	bne	l2			@ repeat it until r1 = 0 
	subs	r1, r1, #1		@ r2 = r2 – 1, decrement r2 (outer loop) 
	bne	l1			@ repeat it until r2 = 0 

	@ terminate the program
	mov   	r7, #1
	svc   0

ASCII:   //regs are wrong currently just skelton code for printing asci
	mov r8, r1 MOD 10 //Remaindar after dividing by 10
	mov r1, r1/10
	mov r6, r8 + 48
	push {r8} 
	cmp R3, ZERO
	bne ASCII 
	
print:
	pop {r8}
	printf(r8)
	bne print
	bx lr
exit:
	MOV R7, #1
	SWI 0



