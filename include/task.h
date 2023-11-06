#ifndef __TASK_H__
#define __TASK_H__

#include"sys.h"

#define MAX_TASK    10
#define STACK_SIZE  1024
typedef int taskid_t;

extern taskid_t taskSize;

extern int task_create(void (*task)(void));
extern void task_go(taskid_t i);
extern void task_os(void);

#endif // !__TASK_H__
