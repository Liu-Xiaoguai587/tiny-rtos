#include"include/os.h"

extern void user_task_init(void);

void os_kernel() {
    uart_init();
    trap_init();

}

int os_main() {
    os_kernel();

    uart_puts("OS start\n");
    trap_test();
    uart_puts("OS end\n");

    while(1);
    return 0;
}
