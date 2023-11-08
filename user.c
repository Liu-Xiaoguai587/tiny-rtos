#include"include/task.h"
#include"include/uart.h"
#include"include/lib.h"

void user_task0(void) {
    uart_puts("Task0 created\n");
    uart_puts("return os\n");
    while(1) {
        uart_puts("Task0 running......\n");
        lib_delay(1000);
        task_os();
    }
}

void user_task1(void) {
    uart_puts("Task1 created\n");
    uart_puts("return os\n");
    while(1) {
        uart_puts("Task1 running......\n");
        lib_delay(1000);
        task_os();
    }
}

void user_task_init() {
    task_create(&user_task0);
    task_create(&user_task1);
}

