@ **NOTE: THIS IS A GROUP ASSEMBLY ASSIGNMENT**

@this code calculates x^2 + 2x + 3 with "x" stored in r9 which you will need to add to the program.  
@Deliverable 1: What is the range of valid values for r9?
@Deliverable 2: Show your code written with R9 added so that it runs with "x = 3".
@Deliverable 3: How many clocks does this take to execute?
@Deliverable 4: Rewrite the function without using a lookup table. Show your code working with "x = 3".  How many clocks to run?
@Deliverable 5: What are pros and cons of the two methods: 1) Look-up table, 2) Mathematical function.


@Deliverable 6: Now write a program with a look-up table that takes a degree value from 0-90 (including 0 and 90) in multiples of 4 (0, 4, 8, 12, etc...) and stores into R9 from the keyboard input.
@ The program will use the degree value and return the sin x 1000 in R0 and the cosine x 1000 in R1 (so this is to 3 decimal places).  For example if R9 = 32, R0 would have 530 and r1 would have 848.  
@ Display the result on the terminal in decimal correctly and with the following format using the example with 32 as the angle...
@ Cosine of 32 = 0.530 and Sine of 32 = 0.848
@ Show your code in your writeup.
@ Code steps: 1) Ask for input "Enter Angle:", 2) If not within range, do nothing, 3) If within range, display the output result and go back to 1) for new input.
@ Deliverable 7: I will check results in class.


	.text
	.global main

main:

	ldr R0, =prompt         @ seed printf 
	bl printf

	ldr r0, =format
	ldr r1, =value
	mov r2, #0
	str r2, [r1]
	bl scanf
	ldr r1, =value                   @loads address of returned int back into r1
	ldr r4, [r1]			 @loads value into r4	
	
      
    mov r1, #0
    cmp r4, r1                       @checks if value is zero       
    beq     Zero

    mov r1, #90
    cmp r4, r1                       @checks if value is zero       
    beq     Ninety


    mov r1, #3                       @mask to check if valid input since 11 is three it check last bit
    and r1,r4,r1                     @any number divisble by 4 should now be 0
    cmp r1, #0
    bne main


	adr r2, Sine			 @stores addres of sine and cosine LuT
	adr r3, Cosine

    ldr r9, [r2, r4]                 @value of sine LuT value is loaded in r9
    ldr r10, [r3, r4]                @val of cosine LuT value is loaded in r10
        


    ldr r0, =seedC                   @Cosine seed

    mov r1, r4                       @load input into r1 //

    mov r2, r10                      @load value into r2 //

    bl printf

    ldr r0, =seedS                   @Sine seed
        
    mov r1, r4                       @load input into r1//

    mov r2, r9                       @laod value into r2//

    bl printf       

        
    b main
Zero:
        ldr r0, =zeroPrompt         @ seed printf 
        bl printf
        b main

Ninety: 
        ldr r0, =ninetyPrompt         @ seed printf 
        bl printf
        b main

End:
        mov r7, #1
        svc     0


Cosine: .word   1000, 998, 990, 978, 961, 940, 914, 883, 848, 809, 766, 791, 669, 616, 560, 500, 438, 375, 309, 242, 174, 105, 35
Sine: .word     0, 70, 139, 208, 276, 342, 407, 470, 530, 588, 643, 695, 743, 788, 829, 866, 899, 927, 951, 970, 985, 995, 999

.data
    prompt:         .asciz "Enter angle: \n"

    zeroPrompt:     .asciz "Cosine of 0 = 1.000 and Sine of 0.000 = 0\n"

    ninetyPrompt:   .asciz "Cosine of 90 = 0.000 and Sine of 90 = 1.000\n"
        
    format:         .asciz "%d"

    value:          .word 0 

    seedC:          .asciz  "Cosine of %d  =  0.%03d and "

    seedS:          .asciz  "Sine of %d  = 0.%03d\n"


	//lookup: .byte	0, 4, 8, 12, 16, 20, 24, 28, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88

	

	

/*
ldr r0, =format
ldr r1, =char
mov r2, #0
strb r2, [r1]
bl scanf
ldr r1, =char                   @loads address of returned char back into r1
ldrb r1, [r1]

LDR R0, =string         @ seed printf
LDR R1, =minutes 
LDR R2, =seconds                @ loads mins into R1 for print
LDR R3, =hundredths
LDR R1, [R1]            @ seed printf
LDR R2, [R2]            @ seed printf
LDR R3, [R3]            @ seed printf
BL printf
 */
