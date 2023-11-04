//#include "include/os.h"
#include "include/stdint.h"

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


void uart_init() {
    //disable interrupts
    uart_write_reg(IER, 0x00);

    //LCR bit7: baud rate counter latch enable
    //set baud rate 38.4k (1.8432 Mhz clock)
    uint8_t lcr = uart_read_reg(LCR);
    uart_write_reg(LCR, lcr | (1 << 7));
    uart_write_reg(DLL, 0x03);
    uart_write_reg(DLM, 0x00);

    //LCR bit 0-1: word length to transmitted or received
    // set length = 8bit
    lcr = 0;
    uart_write_reg(LCR, lcr | 3);
}

int uart_putc(char ch) {
    //LSR bit5: 0,full ; 1, empty
    //wait transmitter register empty
    while((uart_read_reg(LSR) & LSR_TX_IDLE) == 0);
    return uart_write_reg(THR, ch);
}

void uart_puts(char *s) {
    while(*s)
        uart_putc(*s++);
}

