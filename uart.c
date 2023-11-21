#include"include/uart.h"

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
    uart_write_reg(LCR, lcr | (3 << 0));

    uint8_t ier = uart_read_reg(IER);
    uart_write_reg(IER, ier | (1 << 0));
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

int uart_getc() {
    if(uart_read_reg(LSR) & LSR_RX_READY) {
        //return uart_read_reg(RHR) == '\r' ? '\n' : uart_read_reg(RHR);
        return uart_read_reg(RHR);
    } else {
        return -1;
    }
}

char *uart_gets() {
    return (char*)0;
}

void uart_isr() {
    for(;;) {
        int c = uart_getc();
        if(c == -1) {
            break;
        } else {
            uart_putc((char)c);
            uart_putc('\n');
        }
    }
}

void uart_test() {
    uart_puts("-----TEST-----");
}
