@ compiled using gcc exponential.s -o exponential -mfpu=vfpv3
    .text
	.global main
		
main:
	push {lr}



	ldr r0, =stringx
    Bl printf				@prints first part of string

	ldr r0, =formatf
	ldr r1, =x
	bl scanf				@reads the float and stores in x

	ldr r0, =stringn	@prompts for n
	bl printf

	ldr r0, =formatint
	ldr r1, =n				@stores n


	ldr r1, =x
	vldr s0, [r1]			@s0 holds value of x

	ldr r0, =formatf
	vcvt.f64.f32 d0, s0		@ fp to double conversion
	vmov r1, r2, d0
	bl printf				@prints x

	ldr r0, =carrot			@prints ^
	bl printf

	ldr r0, =formatint
	ldr r1, =n	
	ldr r1, [r1]			@prints n




	ldr r0, =n				@r0 holds n
	ldr r0, [r0]
loopn:
	subs r0,r0, #1		@if r0(n) = 1 s0 =s0
	beq exit
	vmul.f32 s0, s0, s0
	b loopn

exit:
	@prints


	ldr r0, output
	vcvt.f64.f32 d0, s0		@ fp to double conversion
	vmov r1, r2, d0			@ prints = result
	bl printf

char:
		.byte  0
output:
		.asciz " = %f"
stringx:
       	.asciz "x^n: x = "
stringn:	
		.asciz "n = "
formatf:
		.asciz "%f"			 	@for reading float	
formatint:
		.asciz "%d"				@for reading int
carrot:
		.asciz "^"
x:
		.word 0						@float to be mul
n:		
		.word 0						@loop tracker

