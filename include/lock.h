#ifndef __LOCK_H__
#define __LOCK_H__

#include"sys.h"

struct spin {
    volatile int locked;
};

extern void lock_init(struct spin *l);
extern void spin_lock(struct spin *l);
extern void spin_unlock(struct spin *l);

#endif // !__LOCK_H__
