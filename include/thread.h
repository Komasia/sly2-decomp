/* Sly 1 thread.h: a critical section built on an EE semaphore. */
#ifndef THREAD_H
#define THREAD_H

typedef struct CRITSECT {
    /* 0x00 */ int cEnter;     /* nesting depth of the owning thread */
    /* 0x04 */ int thread;     /* owning thread id, -1 when free */
    /* 0x08 */ int sema;
} CRITSECT;

#endif
