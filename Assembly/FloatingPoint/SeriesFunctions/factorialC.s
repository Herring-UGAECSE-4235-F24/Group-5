    .text
    .global factorialC

factorialC:
    push {lr}                  @ push link

    vmov.f32 s1, #1.0          @set 1
    vmov.f32 s2, #1.0          
    vmov.f32 s3, #1.0          

    vcmp.f32 s0, #0.0          @ Check zero
    vmrs apsr_nzcv, fpscr
    beq zero                   @ branch to handle corner case

facloop:
    vmul.f32 s1, s1, s0        @ same logic from mi other code
    vsub.f32 s0, s0, s3        @ Decrement 
    vcmp.f32 s0, s2            @ Compare 
    vmrs apsr_nzcv, fpscr
    bne facloop                @ loop until 1

    b exit                     @ Exit when factorial calculation is complete

zero:
    vmov.f32 s1, #1.0          

exit:
    vmov s0, s1                @ return val
    pop {lr}                    
    bx lr                      @ return to e^x
