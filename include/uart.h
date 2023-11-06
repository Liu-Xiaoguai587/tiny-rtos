#include<stdint.h>

#define UART0 0x10000000L

#define UART_REG(reg) ((volatile uint8_t *)(UART0 + reg))

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

#define uart_read_reg(reg)      (*(UART_REG(reg)))
#define uart_write_reg(reg, v)  (*(UART_REG(reg)) = (v))

#define RHR 0
#define THR 0
#define DLL 0
#define IER 1
#define DLM 1
#define FCR 2
#define ISR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SPR 7

extern void uart_init();
extern int uart_putc(char ch);
extern void uart_puts(char *s);

