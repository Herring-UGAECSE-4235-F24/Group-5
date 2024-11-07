    .text
    .global exponentialC
    .func exponentialC

exponentialC:
    push {lr}                   @save link

    vmov s1, s0                 @temps from passed in variables
    mov r2, r0                  

    cmp r2, #0                  
    beq zero                    @ corner case handling for 0

    cmp r2, #1                  
    beq end                     @ corner case handling for 1

loopn:
    subs r2, r2, #1             @ Decrement 
    vmul.f32 s0, s0, s1         @ same as other code logic
    cmp r2, #1                  
    bne loopn                   

    b end                       @ Exit the loop

zero:
    vmov.f32 s0, #1.0           

end:
    pop {lr}                    
    bx lr                       @ return to e^x
