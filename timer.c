#include"include/timer.h"

#define interval 10000000

void timer_init() {
    int id = r_mhartid();   //load hartid
    *(reg_t*)CLINT_MTIMECMP(id) = *(reg_t*)CLINT_MTIME + interval;
    w_mstatus(r_mstatus() | MSTATUS_MIE);   //enable Machine Interrput Enable
    w_mie(r_mie() | MIE_MTIE);  //enable Timer Interrupt Enable
}

static int timer_count = 0;

void timer_handler() {
    lib_printf("timer_handle: %d\n", ++timer_count);
    int id = r_mhartid();
    *(reg_t*)CLINT_MTIMECMP(id) = *(reg_t*)CLINT_MTIME + interval;
}
