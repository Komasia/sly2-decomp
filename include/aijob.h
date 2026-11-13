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

struct LO;
struct KINDE;

/* JOBMOVE (0x9D): a move - an animation index of the guard's mask, its kind entry played; the base of JOBSTAND,
 * JOBSLEEP, JOBB0, JOBB1, ... Layout: SafeHouse port (aijobs.h JOBMOVE). */
typedef struct JOBMOVE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                     /* field: SafeHouse port */
    /* 0x34 */ float tSt;                  /* field: SafeHouse port */
    /* 0x38 */ struct LO *ploFace;         /* field: SafeHouse port - an object to face at the end */
    /* 0x3c */ int nAnim;                  /* field: SafeHouse port - the state index */
    /* 0x40 */ struct KINDE *pkinde;       /* field: SafeHouse port - the entry (null: the best for the mask) */
    /* 0x44 */ char pad44[0x50 - 0x44];
} JOBMOVE;

#endif
