#ifndef __OS_H__
#define __OS_H__

#include"libint.h"
#include"platform.h"
#include"sys.h"

/* uart */
extern void uart_init();
extern int uart_putc(char ch);
extern void uart_puts(char *s);

/* sys */
extern void sys_switch(struct context *old, struct context *new);

/*
// saved registers for kernel context switches
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
}
*/
#endif // !__OS_H__
