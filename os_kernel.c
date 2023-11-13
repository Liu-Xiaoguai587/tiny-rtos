#include"include/os.h"

extern void user_init(void);

void os_start() {
    uart_init();
    trap_init();
    user_init();
    timer_init();

    uart_puts("OS start\n\n");
}

int os_main() {
    os_start();

    pid_t current_task = 0;
    while(1) {
        uart_puts("OS: next task\n");
        task_go(current_task);
        uart_puts("OS: back to OS\n");
        current_task = (current_task + 1) % retTaskNum();
        uart_puts("\n");
    }

    while(1);
    return 0;
}
