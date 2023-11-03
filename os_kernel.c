#include"include/os.h"

#define STACK_SIZE 1024
reg_t task0_stack[STACK_SIZE];
struct context ctx_os;
struct context ctx_task;

int user_task0(int x) {
    uart_puts("Task0: Context Switch Success!\n");

    sys_switch(&ctx_task, &ctx_os);
    return x;
}

int os_main() {
    uart_init();
    uart_puts("OS start\n");

    ctx_task.ra = (reg_t)user_task0;
    ctx_task.sp = (reg_t) &task0_stack[STACK_SIZE-1];
    sys_switch(&ctx_os, &ctx_task);

    uart_puts("OS end\n");
    while(1);
    return 0;
}
