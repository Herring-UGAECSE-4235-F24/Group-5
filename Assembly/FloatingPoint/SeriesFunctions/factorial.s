
@ compiled using=> gcc factorial.s -o fac -mfpu=vfpv3
@ tried using sterlings approximation to calc n! using n^n not enough time for that :()

.text
.align
	.global main
		
main:
	push {lr}


	ldr r0, =stringin
	bl printf

	ldr r0, =format
	ldr r1, =int
	Bl scanf				@keyblock on so it waits for input to start

	ldr r1, =int
	ldr r1, [r1]			@int is in r1

	vldr.f32 s0, [r1]		@s0 = starting point

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


	ldr r0, =intformat
	ldr r1, =int
	bl printf


	ldr r0, =stringout
	vcvt.f64.f32 d0, s0		@ fp to double conversion
	vmov r1, r2, d0
	bl printf

.data
int:
		.word  0
stringin:
       		.asciz "n!: n = "
stringout:
		.asciz "! = %f"
format:
		.asciz "%d"			 	@for reading int	
intformat:
		.asciz "%d"
ec:	
		.float 2.718281

