#include"include/lock.h"

void lock_init(struct spin *l) {
    l->locked = 0;
}

void spin_lock(struct spin *l) {
    for(;;) {
        if(!atomic_swap(l->locked))
            break;
    }
}

void spin_unlock(struct spin *l) {
    l->locked = 0;
}
