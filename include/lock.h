#ifndef __LOCK_H__
#define __LOCK_H__

struct lock {
    volatile tint locked;
};

extern void lock_init(struct lock *l);
extern void lock_acquire(struct lock *l);
extern void lock_free(struct lock *l);

#endif // !__LOCK_H__
