#include"include/lock.h"

void lock_init(struct lock *l) {
    l->locked = 0;
}

void lock_acquire(struct lock *l) {
    for(;;) {
        if(atomic_swap(!l->locked))
            break;
    }
}

void lock_free(struct lock *l) {
    l->locked = 0;
}
