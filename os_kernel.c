#include"include/os.h"

extern void user_task_init(void);

void os_kernel() {
    uart_init();
    trap_init();
    timer_init();

    uart_puts("OS start");
}

int os_main() {
    os_kernel();

    while(1);
    return 0;
}
