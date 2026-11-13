/* AIJOB: the base of the guards' AI jobs (JOBMOVE, JOBSHOOT, JOBSTATION, ...), a BASIC with C++ virtuals
 * (vt slots 7 Init, 8 Enter, 9 Exit, 10 Update, 11 Steer, 12 State, 13 Message, 14 Drive, 15 SetState).
 * Layout: SafeHouse port (ai.h AIJOB). */
#ifndef AIJOB_H
#define AIJOB_H

struct GUARD;

typedef struct AIJOB {
    /* 0x00 */ char pad0[0x10];            /* the BASIC part (vtable, the splice frame / sidebag) */
    /* 0x10 */ struct GUARD *pguard;       /* field: SafeHouse port - the actor running the job */
    /* 0x14 */ struct AIJOB *pparent;      /* field: SafeHouse port */
    /* 0x18 */ struct AIJOB *pchild;       /* field: SafeHouse port */
    /* 0x1c */ int fLocked;                /* field: SafeHouse port - the job holds the actor */
    /* 0x20 */ int cLock;                  /* field: SafeHouse port - the jobs above holding it */
} AIJOB;

#endif
