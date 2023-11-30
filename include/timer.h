#ifndef __TIMER_H__
#define __TIMER_H__

#include "riscv.h"
#include "sys.h"
#include "lib.h"
#include "task.h"
#include "lock.h"

#define NCPU                    8
#define CLINT                   0x2000000
#define CLINT_MTIMECMP(hartid)  (CLINT + 0x4000 + 4*(hartid))
#define CLINT_MTIME             (CLINT + 0xBFF8)
#define interval 10000000
//timer interrupt
#define MAX_SOFTWARE_TIMER  10

struct timer {
    void (*func)(void *arg);
    void *arg;
    int time_out;
};

extern void timer_init();
extern void timer_handler();
//software interrupt
extern void software_timer_init(void);
extern struct timer *software_timer_create(void (*handler)(void*), void *arg, uint32_t timeout);
extern void software_timer_delete(struct timer *software_timer);

#endif // !__TIMER_H__
