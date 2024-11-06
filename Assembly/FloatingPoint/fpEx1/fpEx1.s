@ Group assignment
@ This program calculates the area of a circle
@ use gdb info all-registers  or i all-r
@ Change the code to print the results to the monitor in correct format.
@ We will check in class.  Be ready to change the radius value and re-run

@compile => gcc fpEx1.s -o fpEx1 -mfpu=vfpv3
	.text
	.global main
		
main:
	push {lr}
	vmov.f32	s0, #0.125
	vmul.f32 	s0, s0, s0		@r^2
	ldr	r2,=piNumber
	vldr		s1, [r2]
	vmul.f32	s0, s0, s1		@area
	
	vcvt.f64.f32 d0, s0		@ fp to double conversion
	ldr r0, =string
	vmov r1, r2, d0
	bl printf
	
exit: 
	mov R7, #1          @service command code 1 
	svc     0               @call linux to terminate

.data
string:
    .asciz "The area of your circle is:  %f units squared \n"

piNumber:
	.float 3.141593
