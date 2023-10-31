extern void uart_init();
extern void uart_puts(char *s);

void os_main() {
    uart_init();
    uart_puts("Hello World");
    while(1);
}
