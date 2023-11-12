#ifndef __RISCV_H__
#define __RISCV_H__

#include<stdint.h>

typedef uint32_t reg_t;

struct context {
    reg_t ra;
    reg_t sp;

    //saved registers
    reg_t s0;
    reg_t s1;
    reg_t s2;
    reg_t s3;
    reg_t s4;
    reg_t s5;
    reg_t s6;
    reg_t s7;
    reg_t s8;
    reg_t s9;
    reg_t s10;
    reg_t s11;
};

static inline reg_t r_mhartid() {
    reg_t v;
    asm volatile("csrr %0, mhartid" : "=r" (v) );
    return v;
}

/*-------------Machine Status Register--------------
 *
 *      MSTATUS[10:11] Machine Previous Privilege
 *      00 => User
 *      01 => Supervisor
 *      11 => Machine
 *
 *      MSTATUS[3] Machine Interrput Enable
 *      1 => enable
 *      0 => disable
 *-------------------------------------------------*/
#define MSTATUS_MPP_MASK    (3 << 11)
#define MSTATUS_MPP_M       (3 << 11)
#define MSTATUS_MPP_S       (1 << 11)
#define MSTATUS_MPP_U       (1 << 11)
#define MSTATUS_MIE         (1 << 3)

static inline reg_t r_mstatus() {
    reg_t v;
    asm volatile("csrr %0, mstatus" : "=r" (v) );
    return v;
}

static inline void w_mstatus(reg_t v) {
    asm volatile("csrw mstatus, %0" : : "r" (v) );
}


// machine exception program counter registers
static inline reg_t r_mepc() {
    reg_t v;
    asm volatile("csrr %0, mepc" : "=r" (v) );
    return v;
}

static inline void w_mepc(reg_t v) {
    asm volatile("csrw mepc, %0" : : "r" (v) );
}


// Machine Scratch registers
static inline void w_mscratch(reg_t v) {
    asm volatile("csrw mscratch, %0" : : "r"  (v) );
}


// Machine Trip Vector registers
static inline void w_mtvec(reg_t v) {
    asm volatile("csrw mtvec, %0" : : "r" (v) );
}


/*--------Machine Interrupt Enable registers--------
 *
 *      MIE[11] External Interrput Enable
 *      MIE[7]  Timer Interrupt Enable
 *      MIE[3]  Soft Interrupt Enable
 *      1 => enable
 *      2 => disable
 *-------------------------------------------------*/
#define MIE_MEIE    (1 << 11)
#define MIE_MTIE    (1 << 7)
#define MIE_MSIE    (1 << 3)

static inline reg_t r_mie() {
    reg_t v;
    asm volatile("csrr %0, mie" : "=r" (v) );
    return v;
}

static inline void w_mie(reg_t v) {
    asm volatile("csrw mie, %0" : : "r" (v) );
}

#endif // !__RISCV_H__
