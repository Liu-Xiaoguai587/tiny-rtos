#ifndef __MEM_H__
#define __MEM_H__

#include "riscv.h"
#include "lock.h"

extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;

typedef char ALIGN[12];

union header {
    struct {
        size_t size;
        unsigned is_free;
        union header* next;
    }s;
    ALIGN stub;
};
typedef union header header_t;

void memory_init();
char *sbrk(int size);
void *malloc(size_t size);
header_t *get_free_block(size_t size);
void free(void *block);

#endif  //__MEM_H__