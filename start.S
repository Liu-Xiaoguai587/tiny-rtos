#include "include/platform.h"

.equ    STACK_SIZE, 8192

.global _start
.text

_start:
    csrr    t0, mhartid
    mv      tp, t0
    bnez    t0, park

    slli    t0, t0, 10              # hart time 1024
    la      sp, stacks + STACK_SIZE # initzation stack pointer base address
    add     sp, sp, t0              # allocate current hart stack pointer

    j       os_main

park:
    wfi                             #sleep
    j       park


stacks:
    .skip   STACK_SIZE * MAXNUM_CPU

.end        #end .text
