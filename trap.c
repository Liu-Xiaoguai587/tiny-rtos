#include"include/trap.h"

extern void os_kernel();

void trap_init() {
    w_mstatus(r_mstatus() | MSTATUS_MIE);
    w_mtvec((reg_t) sys_trapVec);
}

void external_handler() {
    uart_test();
    int irq = plic_claim();
    if(irq == UART0_IRQ) {
        uart_isr();
    }else if(irq) {
        lib_printf("unexpected interrupt irq = %d\n", irq);
    }

    if(irq) {
        plic_complete(irq);
    }
}

reg_t trap_handler(reg_t epc, reg_t cause) {
    reg_t ret_pc = epc;
    reg_t cause_code = cause & 0xfff;

    if(cause & 0x80000000) {
        switch(cause_code) {
            case 3:
                lib_printf("M: software interrupt\n");
                break;
            case 7:
                uart_puts("M: timer interrupt\n");
                // disable machine timer interrupt
                w_mie(~((~r_mie()) | MIE_MTIE));
                timer_handler();
                ret_pc = (reg_t)task_os;
                //enable machine timer interrupt
                w_mie(r_mie() | MIE_MTIE);
                break;
            case 11:
                uart_puts("M: external interrupt\n");
                external_handler();
                break;
        }
    } else {
        lib_printf("Sync, code = %d\n", cause_code);
        //ret_pc += 4;
        uart_puts("ERROR\n");
        while(1);
    }
    return ret_pc;
}

void trap_test() {
    *(int *)0x00000000 = 50;

    //lib_printf("Trap_test END\n");
    uart_puts("   Trap_test END\n");
}
