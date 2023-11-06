#ifndef __SYS_H__
#define __SYS_H__

#include<stdint.h>


// saved registers for kernel context switches
//typedef reg_t uint32_t;
typedef uint32_t reg_t;

struct context {
    reg_t ra;
    reg_t sp;

    //saved registers
    reg_t s0;
    reg_t s1;
    reg_t s2;
    reg_t s3;
    reg_t s4;
    reg_t s5;
    reg_t s6;
    reg_t s7;
    reg_t s8;
    reg_t s9;
    reg_t s10;
    reg_t s11;
};

extern void sys_switch(struct context *old, struct context *new);

#endif // !__SYS_H__
