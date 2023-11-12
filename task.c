#include"include/task.h"

uint8_t task_stack[MAX_TASK][STACK_SIZE];
struct context ctx_os;
struct context ctx_tasks[MAX_TASK];
struct context *ctx_now;
static pid_t taskNum = 0;

pid_t retTaskNum() {
    return taskNum;
}

pid_t task_create(void (*task)(void)) {
    pid_t i = taskNum++;
    ctx_tasks[i].ra = (reg_t)task;
    ctx_tasks[i].sp = (reg_t)&task_stack[i][STACK_SIZE - 1];
    return i;
}

void task_go(pid_t i) {
    ctx_now = &ctx_tasks[i];
    sys_switch(&ctx_os, &ctx_tasks[i]);
}

void task_os(void) {
    struct context *ctx = ctx_now;
    ctx_now = &ctx_os;
    sys_switch(ctx, &ctx_os);
}

