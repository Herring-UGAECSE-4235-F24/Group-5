
@ Constants for blink at GPIO21
@ GPFSEL2 [Offset: 0x08] responsible for GPIO Pins 20 to 29
@ GPCLR0 [Offset: 0x28] responsible for GPIO Pins 0 to 31
@ GPSET0 [Offest: 0x1C] responsible for GPIO Pins 0 to 31

@ GPOI21 Related
.equ    GPFSEL2, 0x08   @ function register offset
.equ    GPCLR0, 0x28    @ clear register offset
.equ    GPSET0, 0x1c    @ set register offset
.equ    GPFSEL2_GPIO21_MASK, 0b111000000   @ Mask for fn register for gpio 22
.equ    MAKE_GPIO21_OUTPUT, 0b001000000      @ use pin for ouput
.equ    PIN, 22                         @ Used to set PIN high / low

@ Args for mmap
.equ    OFFSET_FILE_DESCRP, 0   @ file descriptor
.equ    mem_fd_open, 3
.equ    BLOCK_SIZE, 4096        @ Raspbian memory page
.equ    ADDRESS_ARG, 3          @ device address

@ Misc
.equ    SLEEP_IN_S,1            @ sleep one second

@ The following are defined in /usr/include/asm-generic/mman-common.h:
.equ    MAP_SHARED,1    @ share changes with other processes
.equ    PROT_RDWR,0x3   @ PROT_READ(0x1)|PROT_WRITE(0x2)

@ On time and off time variables in one nano second intervals
ON_TIME:
   .word 4500000 @100 Hz
   @.word 450000 @1k Hz
   @.word 675000 @1k 75% high
OFF_TIME:
   .word 4500000 @100Hz
   @.word 450000 @1k Hz
   @.word 225000 @1k 25% low
@ Constant program data
    .section .rodata
device:
    .asciz  "/dev/gpiomem"


@ The program
    .text
    .global main
main:
@ Open /dev/gpiomem for read/write and syncing
    ldr     r1, O_RDWR_O_SYNC   @ flags for accessing device
    ldr     r0, mem_fd          @ address of /dev/gpiomem
    bl      open     
    mov     r4, r0              @ use r4 for file descriptor

@ Map the GPIO registers to a main memory location so we can access them
@ mmap(addr[r0], length[r1], protection[r2], flags[r3], fd[r4])
    str     r4, [sp, #OFFSET_FILE_DESCRP]   @ r4=/dev/gpiomem file descriptor
    ldr     r6, #ON_TIME  @delay value
    ldr     r7, #OFF_TIME
    mov     r1, #BLOCK_SIZE                 @ r1=get 1 page of memory
    mov     r2, #PROT_RDWR                  @ r2=read/write this memory
    mov     r3, #MAP_SHARED                 @ r3=share with other processes
    mov     r0, #mem_fd_open                @ address of /dev/gpiomem
    ldr     r0, GPIO_BASE                   @ address of GPIO
    str     r0, [sp, #ADDRESS_ARG]          @ r0=location of GPIO
    bl      mmap
    mov     r5, r0           @ save the virtual memory address in r5

@ Set up the GPIO pin funtion register in programming memory
    add     r0, r5, #GPFSEL2            @ calculate address for GPFSEL2
    ldr     r2, [r0]                    @ get entire GPFSEL2 register
    bic     r2, r2, #GPFSEL2_GPIO21_MASK@ clear pin field
    orr     r2, r2, #MAKE_GPIO21_OUTPUT @ enter function code
    str     r2, [r0]                    @ update register


ON:
@ Turn on
    add     r0, r5, #GPSET0 @ calc GPSET0 address

    mov     r3, #1          @ turn on bit
    lsl     r3, r3, #PIN    @ shift bit to pin position
    orr     r2, r2, r3      @ set bit
    str     r2, [r0]        @ update register
    bl DELAY_ON
    b OFF

OFF:
@ Turn off
    add     r0, r5, #GPCLR0 @ calc GPCLR0 address

    mov     r3, #1          @ turn off bit
    lsl     r3, r3, #PIN    @ shift bit to pin position
    orr     r2, r2, r3      @ set bit
    str     r2, [r0]        @ update register
    bl 	    DELAY_OFF
    b       ON

DELAY_ON:
    subs    r6, r6, #1       
    bne     DELAY_ON             @ Loop until R1 becomes zero
    ldr     r6, #ON_TIME
    bx      lr               @ Return to call

DELAY_OFF: 
    subs    r7, r7, #1
    bne     DELAY_OFF		 @ Loop until R7 becomes zero
    ldr     r7, #OFF_TIME
    bx      lr              @ Return to call

GPIO_BASE:
    .word   0xfe200000  @GPIO Base address Raspberry pi 4
mem_fd:
    .word   device
O_RDWR_O_SYNC:
    .word   2|256       @ O_RDWR (2)|O_SYNC (256).
