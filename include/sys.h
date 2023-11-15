#ifndef __SYS_H__
#define __SYS_H__

#include"riscv.h"
#include"trap.h"

#include"uart.h"
// saved registers for kernel context switches
//typedef reg_t uint32_t;

extern void sys_switch(struct context *old, struct context *new);
extern void sys_trapVec();

extern void aomic_swap();

#endif // !__SYS_H__
