#ifndef __PLIC_H__

#include"riscv.h"

#define PLIC_BASE           0x0c000000L
#define PLIC_PRIORITY(id)   (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id)    (PLIC_BASE + 0x1000 + ((id) / 32))
#define PLIC_MENABLE(hart)  (PLIC_BASE + 0x2000 + (hart) * 0x80)
#define PLIC_MCLAIM(hart)   (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MCOMPLETE(hart)    (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MTHRESHOLD(hart)   (PLIC_BASE + 0x200000 + (hart) * 0x1000)

#define UART0_IRQ 10


extern void plic_init();
extern int plic_claim();
extern void plic_complete(int irq);

#endif // !__PLIC_H__
