
@ compiled using=> gcc factorial.s -o fac -mfpu=vfpv3 -lc
@ tried using sterlings approximation to calc n! using n^n not enough time for that :()

	.text
	.global main
		
main:
	push {lr}
	ldr r0, =prompt
	bl printf


	ldr r0, =int
	ldr r1, =in
	bl scanf				@keyblock on so it waits for input to start

	ldr r0, =in

	vldr.f32 s0, [r0]		@s0 = starting point

	ldr r1, [r1]			@int is in r1


	vmov.f32 s1, #1.0		@result val
	vmov.f32 s2, #1.0		@temp for next iteration
	vmov.f32 s3, #1.0
facloop:
	vmul.f32 s1, s1, s0		@if s0 = 5 s1 = 5
	vcmp.f32 s0, s2		@if s0 = 1 exit
	beq exit

	vsub.f32 s0, s0, s3	@s2 = s0 - 1 aka one less
	
	b facloop

exit:


	ldr r0, =int
	ldr r1, =in
	bl printf


	ldr r0, =stringout
	vcvt.f64.f32 d0, s0		@ fp to double conversion
	vmov r1, r2, d0
	bl printf

	
	.data
	
	x:
		.word 0						@storing input
	string:
                .asciz "Sin(x) = %f\n"       			@output string
	float:
		.asciz "%f"					@format string floats
	prompt:
                .asciz "Sin(x):   x = "			@entry prompt

	
	

