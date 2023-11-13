#include"include/timer.h"

#define interval 10000000

reg_t timer_scratch[NCPU][5];

void timer_init() {
    int id = r_mhartid();
    *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + interval;

    // prepare information in scratch[] for timervec.
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired interval (in cycles) between timer interrupts.
    reg_t *scratch = &timer_scratch[id][0];
    scratch[3] = CLINT_MTIMECMP(id);
    scratch[4] = interval;
    w_mscratch((reg_t)scratch);

    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);
}

static int timer_count = 0;

void timer_handler() {
    lib_printf("timer_handle: %d\n", ++timer_count);
    int id = r_mhartid();
    *(reg_t*)CLINT_MTIMECMP(id) = *(reg_t*)CLINT_MTIME + interval;
}
