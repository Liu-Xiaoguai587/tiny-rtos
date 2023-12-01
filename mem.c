#include "include/mem.h"

static char *_brk;
struct spin malloc_lock;
header_t *head = NULL, *tail = NULL;

void memory_init() {
    lib_printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
    lib_printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
    lib_printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
    lib_printf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
    lib_printf("HEAP:   0x%x -> 0x%x\n", HEAP_START, HEAP_START + HEAP_SIZE);

    _brk = (char *)HEAP_START;
    lock_init(&malloc_lock);
}

char *sbrk(int size) {
    char *tmp = _brk;
    _brk += size;
    return tmp;
}

void *malloc(size_t size) {
    header_t *header;
    void *block;
    size_t total_size;

    if(size == 0) 
        return NULL;
    spin_lock(&malloc_lock);

    header = get_free_block(size);
    if(header != NULL) {
        header->s.is_free = 0;
        spin_unlock(&malloc_lock);
        return (void *)(header + 1);
    }

    total_size = sizeof(header_t) + size;
    block = sbrk(total_size);
    if(block == (void *) -1) {
        spin_unlock(&malloc_lock);
        return NULL;
    }
    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if(head == NULL)
        head = header;
    if(tail != NULL)
        tail->s.next = header;
    tail = header;
    spin_unlock(&malloc_lock);
    return (void *)(header + 1);
}

header_t *get_free_block(size_t size) {
    header_t *curr = head;
    while(curr != NULL) {
        if(curr->s.is_free == 0 && curr->s.size > size)
            return curr;
        curr = curr->s.next;
    }
    return NULL;
}

void free(void *block) {
    header_t *header;
    void *programbreak;

    if(block == NULL)
        return;

    spin_lock(&malloc_lock);
    header = (header_t *)block -1;
    programbreak = sbrk(0);
    if((char *) block + header->s.size == programbreak) {
        if(head == tail)
            head = tail = NULL;

        header_t *tmp = head;
        while(tmp) {
            if(tmp->s.next == tail) {
                tmp->s.next = NULL;
                tail = tmp;
                //break;
            }
            tmp = tmp->s.next;
        }
        sbrk(0 - sizeof(header_t) - header->s.size);
        spin_unlock(&malloc_lock);
        return;
    }

    header->s.is_free = 1;
    spin_unlock(&malloc_lock);
}

