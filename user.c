#include"include/task.h"
#include"include/uart.h"
#include"include/lib.h"
#include"include/riscv.h"

void user_task0(void) {
    uart_puts("Task0 created\n");
    while(1) {
        uart_puts("Task0 running......\n");
        lib_delay(1000);
    }
}

void user_task1(void) {
    uart_puts("Task1 created\n");
    while(1) {
        int hart_id = r_mhartid();
        lib_printf("hart id is %d\n", hart_id);
        uart_puts("Task1 running......\n");
        lib_delay(1000);
    }
}

void user_init() {
    task_create(&user_task0);
    task_create(&user_task1);
}

