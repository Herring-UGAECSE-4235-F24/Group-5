	.global main
    .func main



main:
    LDR R0, =string         @ seed printf
    LDR R1, =minutes 
    LDR R2, =seconds		@ loads mins into R1 for print
    LDR R3, =hundredths
    LDR R1, [R1]            @ seed printf
    LDR R2, [R2]            @ seed printf
    LDR R3, [R3]            @ seed printf
    BL printf
	
    ldr r0, =format
    ldr r1, =char
    Bl scanf	
    ldr r1, =char                   @loads address of returned char back into r1
    ldrb r1, [r1]
    cmp r1, #'c'                    @ how you compare chars			@keyblock on so it waits for input to start
    beq deblock
    cmp r1, #'q'
    beq	exit
    
deblock:
    mov r0, #1    @sets deblock to 1
    bl E4235_KYBdeblock
    @cmp r0, #0
    @beq exit
    b main 
	
	
_exit:
	mov     R0, #0          @use 0 return code
	mov     R7, #1          @service command code 1 
	svc     0               @call linux to terminate

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
