
@ compiled using=> gcc factorial.s -o fac -mfpu=vfpv3 
@ tried using sterlings approximation to calc n! using n^n not enough time for that :()
@ 13 is correct 14 it breaks
	.text
	.global main
		
main:
	push {LR}

	ldr r0, =prompt	@seed printf with prompt
	bl printf
	
	ldr r0, =fp		@seed scanf to take n
	ldr r1, =n
	bl scanf
	
	ldr r0, =n		
	vldr s0, [r0]
	vcvt.f64.f32 d0, s0 @float to double since floats don't print
	vmov r1, r2, d0
	ldr r0, =fp		@prints x
	bl printf


	ldr r0, =n		@load floating point
	vldr s0, [r0]


	vmov.f32 s1, #1.0		@result val
	vmov.f32 s2, #1.0		@temp for next iteration
	vmov.f32 s3, #1.0
	
	vcmp.f32 s0, #0.0
	vmrs apsr_nzcv, fpscr
	beq zero
facloop:
	vmul.f32 s1, s1, s0		@if s0 = 3 s1 = 3, S0 = 2, s1 = 6, S0 = 1, exit s1 holds val 
	vcmp.f32 s0, s2		@if s0 = 1 exit
	vmrs apsr_nzcv, fpscr
	beq exit

	vsub.f32 s0, s0, s3	@s2 = s0 - 1 aka one less
	
	b facloop
zero:
	vmov.f32 s0, #1.0

exit:	

	vcvt.f64.f32 d0, s1	@single to double
	ldr r0, =string
	vmov r1, r2, d0
	bl printf


    pop {pc}
    MOV pc, lr
	
	
	
.data
n:	
	.word 0						@input value
prompt: 
	.asciz "N! please enter n: "	@prompt

string: 
	.asciz "! = %f\n"			


@ int
@ 	.asciz "%d"	
fp:  
	.asciz "%f"				@format string


	
