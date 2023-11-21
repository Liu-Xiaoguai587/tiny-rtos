#include"riscv.h"
#include"sys.h"
#include"lib.h"
#include"timer.h"
#include"task.h"
#include"plic.h"

extern void trap_init();
extern void external_handler();
extern reg_t trap_handler(reg_t epc, reg_t cause);
extern void trap_test();
