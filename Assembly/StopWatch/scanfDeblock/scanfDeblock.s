	.global main
    .func main



main:
	ldr r0, =format
    	ldr r1, =char
    	Bl scanf	
	ldr r1, =char                   @loads address of returned char back into r1
        ldrb r1, [r1]
        cmp r1, #'c'                    @ how you compare chars			@keyblock on so it waits for input to start
	@beq _On @key deblock is now on
		
	ldr r1, =char
	mov r2, #0
	str r2, [r1]
	ldr r0, =format
	ldr r1, =char
	Bl scanf				@keyblock on so it waits for input to start
	ldr r1, =char 
	ldrb r1, [r1]
        cmp r1, #'c'
	b exit @should exit before input is needed

	
	cmp r1, #0x63			@ 0x63 is hex of c testing if this is how you compare chars
	beq _exit
reset:	
	mov r1, #1000
loop: 
	bl printloop
	subs r1, r1, #1
	bne loop
	beq reset


printloop:
	LDR R0, =string         @ seed printf
    	LDR R1, =minutes 
        LDR R2, =seconds		@ loads mins into R1 for print
        LDR R3, =hundredths
    	LDR R1, [R1]            @ seed printf
        LDR R2, [R2]            @ seed printf
        LDR R3, [R3]            @ seed printf
    	BL printf
		bx lr
_Off:		@from class lib
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
_On: 		@from class lib
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
		.byte  0
string:
       	.asciz " %c"
format:
		.asciz " %c"			 	@for reading char	
hundredths:
	    .word   0               @ hundreths count storage for printing
seconds:
		.word 	0 				@ seconds count storage for print
minutes:
		.word	0				@ minutes count for print
