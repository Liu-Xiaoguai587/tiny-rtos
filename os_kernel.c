#include"include/os.h"

#define STACK_SIZE 1024


int os_main() {
    uart_init();
    uart_puts("OS start\n");

    uart_puts("OS end\n");
    while(1);
    return 0;
}
