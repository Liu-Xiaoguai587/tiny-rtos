#include"include/trap.h"

void trap_init() {
    w_mtvec((reg_t) sys_trapVec);
}

reg_t trap_handler(reg_t epc, reg_t cause) {
    reg_t ret_pc = epc;
    reg_t cause_code = cause & 0xfff;

    if(cause & 0x80000000) {
        switch(cause_code) {
            case 3:
                lib_printf("software interrupt\n");
                break;
            case 7:
                lib_printf("timer interrupt\n");
                break;
            case 11:
                lib_printf("external interrupt\n");
                break;
        }
    } else {
        lib_printf("Sync, code = %d\n", cause_code);
        //ret_pc += 4;
    }
    return ret_pc;
}

void trap_test() {
    *(int *)0x00000000 = 50;

    //lib_printf("Trap_test END\n");
    uart_puts("   Trap_test END\n");
}
