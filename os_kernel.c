#include"include/os.h"

extern void user_task_init(void);

int os_main() {
    uart_init();
    user_task_init();
    uart_puts("OS start\n");

    pid_t current_task = 0;
    while(1) {
        task_go(current_task);
        uart_puts("returned OS\n\n");
        current_task = (current_task + 1) % retTaskNum();
    }

    return 0;
}
