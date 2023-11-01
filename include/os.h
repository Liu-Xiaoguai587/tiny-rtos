#ifndef __OS_H__
#define __OS_H__

#include"stdint.h"
#include"platform.h"

/* uart */
extern int uart_putc(char ch);
extern void uart_puts(char *s);



#endif // !__OS_H__
