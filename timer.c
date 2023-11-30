#include"include/timer.h"


reg_t timer_scratch[NCPU][31];

void timer_init() {
    int id = r_mhartid();
    *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + interval;

    // prepare information in scratch[] for timervec.
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired interval (in cycles) between timer interrupts.
    reg_t *scratch = &timer_scratch[id][0];
    //scratch[3] = CLINT_MTIMECMP(id);
    //scratch[4] = interval;
    w_mscratch((reg_t)scratch);

    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);
}

static int timer_count = 0;

void timer_handler() {
    timer_count++;
    lib_printf("timer_handle: %d\n", timer_count);
    softwork_timer_check();
    int id = r_mhartid();
    *(reg_t*)CLINT_MTIMECMP(id) = *(reg_t*)CLINT_MTIME + interval;
}

//
//  softwork interrupt
//
static struct timer timer_list[MAX_SOFTWORK_TIMER];
struct spin softwork_timer_lock;

void softwork_timer_init(void) {
    lock_init(&softwork_timer_lock);
    struct timer *t = timer_list;
    for(int i = 0; i < MAX_SOFTWORK_TIMER; i++) {
        t->func = NULL;
        t->arg = NULL;
        t++;
    }
}

struct timer *softwork_timer_create(void (*handler)(void*), void *arg, uint32_t timeout) {
    if(handler == NULL || timeout == 0)
        return NULL; 

    spin_lock(&softwork_timer_lock);

    struct timer *t = &(timer_list[0]);
    for(int i = 0; i < MAX_SOFTWORK_TIMER; i++) {
        if(t->func == NULL)
            break;
        
        t++;
    }
    if(t->func == NULL) {
        spin_unlock(&softwork_timer_lock);
        return NULL;
    }

    t->func = handler;
    t->arg = arg;
    t->time_out = timer_count + timeout;

    spin_unlock(&softwork_timer_lock);

    return t;
}

void softwork_timer_delete(struct timer *soft_timer) {
    spin_lock(&softwork_timer_lock);

    soft_timer->func = NULL;
    soft_timer->arg = NULL;

    spin_unlock(&softwork_timer_lock);
}

void softwork_timer_check() {
    struct timer *t = timer_list;
    for(int i = 0; i < MAX_SOFTWORK_TIMER; i++) {
        if(t->func == NULL)
            continue;

        if(timer_count == t->time_out) {
            t->func(t->arg);

            //only interrupt once
            t->func = NULL;
            t->arg = NULL; 
        }
        t++;
    }
}

