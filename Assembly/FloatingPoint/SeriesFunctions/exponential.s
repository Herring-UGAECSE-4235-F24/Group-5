	@ compiled using gcc exponential.s -o exponential -mfpu=vfpv3
	.text
	.global main


	
main:
	push {lr}

	ldr r0, =promptx		@seed printf with prompt for x
	bl printf

	ldr r0, =float		@reads user input for base
	ldr r1, =x
	bl scanf

	ldr r0, =promptn		@seed printf with prompt for n
	bl printf
	
	ldr r0, =int	@reads n for exponent
	ldr r1, =n
	bl scanf
	
	ldr r0, =x		@converting x to double and printing
	vldr s0, [r0]
	vcvt.f64.f32 d0, s0	
	vmov r1, r2, d0
	ldr r0, =float
	bl printf

	ldr r0, =n	@printing n
	ldr r1, [r0]
	ldr r0, =carrot
	bl printf

	
	ldr r0, =x	@storing x and n into their respective registers
	vldr s0, [r0]

	ldr r1, =n
	ldr r0, [r1]
	
	
	cmp r0, #0			@checking for zero exponent
	beq zero		@if so, print 1

	vmov.f32 s1, s0

loopn:
	subs r0,r0, #1		@if r0(n) = 1 s0 =s0
	beq exit
	vmul.f32 s1, s1, s0
	b loopn
	
zero:
	vmov.f32 s1, #1
exit:

	vcvt.f64.f32 d0, s1	@convert to double and print
	ldr r0, =equal
	vmov r1, r2, d0
	bl printf

    pop {pc}
    mov pc, lr
		
.data
x:	
	.word 0								@storing x
n: 
	.word 0							@storing n
promptx:
	 .asciz "x^n => please enter x: "	@startup message
promptn:
	 .asciz "please enter n: "					@enter n message
carrot: 
	.asciz "^%d"							
int: 
	.asciz "%d"						@reading in an int
float: 
	 .asciz "%f"							@reading in a float
equal:
	 .asciz " => %f\n"					@printing in pieces to avoid using stack


