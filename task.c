#include"include/task.h"

uint8_t task_stack[MAX_TASK][STACK_SIZE];
struct context ctx_os;
struct context ctx_tasks[MAX_TASK];
struct context *ctx_now;
taskid_t taskSize = 0;


int task_create(void (*task)(void)) {
    taskid_t i = taskSize++;
    ctx_tasks[i].ra = (reg_t)task;
    ctx_tasks[i].sp = (reg_t)&task_stack[i][STACK_SIZE - 1];
    return i;
}

void task_go(taskid_t i) {
    ctx_now = &ctx_tasks[i];
    sys_switch(&ctx_os, &ctx_tasks[i]);
}

void task_os(void) {
    struct context *ctx = ctx_now;
    ctx_now = &ctx_os;
    sys_switch(ctx, &ctx_os);
}
