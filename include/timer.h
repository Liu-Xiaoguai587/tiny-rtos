#ifndef __TIMER_H__
#define __TIMER_H__

#include "riscv.h"
#include "sys.h"
#include "lib.h"
#include "task.h"

#define NCPU                    8
#define CLINT                   0x2000000
#define CLINT_MTIMECMP(hartid)  (CLINT + 0x4000 + 4*(hartid))
#define CLINT_MTIME             (CLINT + 0xBFF8)

extern void timer_init();
extern void timer_handler();

#endif // !__TIMER_H__
