	.global main
    .func main



main:
	ldr r0, =format
    ldr r1, =char
    Bl scanf				@keyblock on so it waits for input to start
	ldr r1, =char			@loads address of returned char back into r1
	ldr r1, [r1]			@actual value of char now in r1
	cmp r1, 0x63			@ 0x63 is hex of c testing if this is how you compare chars
	beq _KeyBlockOff

	ldr r0, =format
    ldr r1, =char
	Bl scanf				@keyblock on so it waits for input to start
	ldr r1, =char
	cmp r1, 0x63			@ 0x63 is hex of c testing if this is how you compare chars
	beq _exit
reset:	
	ldr r1, #100000
loop: 
	subs r1, r1, #1
	bne loop
	beq reset

_KeyBlockOff:		@from class lib
    mov r0, #0 	    @ file descriptor for stdin
	mov r1, #3	    @ get F_GETFL
	bl fcntl
	mvn r2, #2048	@ set inverse O_NONBLOCK
	and r1, r1, r2	@ combine flags
	mov r2, r1
	mov r0, #0	    @ file descriptor for stdin
	mov r1, #4	    @ set F_SETFL
    bl fcntl
	bx lr
_KeyBlockOn: 		@from class lib
    mov r0, #0 	    @ file descriptor for stdin
	mov r1, #3	    @ get F_GETFL
	bl fcntl
	mov r2, #2048	@ set O_NONBLOCK
	orr r1, r1, r2	@ combine flags
	mov r2, r1
	mov r0, #0	    @ file descriptor for stdin
	mov r1, #4	    @ set F_SETFL
    bl fcntl
	bx lr
_exit:
	mov     R0, #0          @use 0 return code
	mov     R7, #1          @service command code 1 
	svc     0               @call linux to terminate

.data
char:
		.asciz ""
string:
       	.asciz "%c"
format:
		.asciz "%c"			 	@for reading char	
hundredths:
	    .word   0               @ hundreths count storage for printing
seconds:
		.word 	0 				@ seconds count storage for print
minutes:
		.word	0				@ minutes count for print
