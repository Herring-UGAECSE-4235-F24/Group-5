


ldr r0, =format
ldr r1, =char
Bl scanf				@keyblock on so it waits for input to start
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
