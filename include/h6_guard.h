/* The guards' animation kinds (GUARD's kind table +0x4C0 / +0x4D0 and the three arrays +0x8D0..): each kind entry
 * maps a set of guard states (a mask of GRFGS bits) to what plays for them. Layouts after SafeHouse's guard.h
 * (field: SafeHouse port). */
#ifndef H6_GUARD_H
#define H6_GUARD_H

/* KINDE::k */
enum KINDK {
    KINDK_None = -1,
    KINDK_Aseg = 0,     /* an ASEG */
    KINDK_Sm = 1,       /* an SM */
    KINDK_Kind2 = 2,    /* a KIND2: an ASEG moved in steps by its events 0x22 / 0x23 / 0x24 */
    KINDK_Kind3 = 3     /* a KIND3: four directional clips */
};

/* a kind-2 object (0x40 bytes) */
typedef struct KIND2 {
    /* 0x00 */ int oid;          /* the ASEG's oid (before the first resolve) */
    /* 0x04 */ void *paseg;
    /* 0x08 */ char pad8[0x38];
} KIND2;

/* K2PLAY::st: the kind-2 player's states (the guard's +0xDB0) */
enum K2ST {
    K2ST_None = -1,
    K2ST_Start = 0,     /* playing up to the event 0x22 */
    K2ST_Air = 1,       /* in the air toward the target */
    K2ST_Fall = 2,      /* past the event 0x23's time */
    K2ST_Land = 3,      /* landed (the event 0x24's time) */
    K2ST_Done = 4
};

/* one direction of a kind-3 object (0x30 bytes) */
typedef struct KIND3E {
    /* 0x00 */ union {
                   int oid;      /* before the resolve */
                   void *paseg;  /* after it (ResolveK3) */
               } u;
    /* 0x04 */ char pad4[0xC];
    /* 0x10 */ char vel[0x10];   /* the root's mean velocity */
    /* 0x20 */ float s20;        /* its length */
    /* 0x24 */ char pad24[0xC];
} KIND3E;

/* a kind-3 object (0xD0 bytes) */
typedef struct KIND3 {
    /* 0x00 */ KIND3E ae[4];
    /* 0xc0 */ int fResolved;
    /* 0xc4 */ char padC4[0xC];
} KIND3;

/* a kind entry */
typedef struct KINDE {
    /* 0x00 */ int k;            /* KINDK_* */
    /* 0x04 */ union {
                   int oid;      /* before the resolve */
                   void *plo;    /* KINDK_Aseg / KINDK_Sm: the ASEG / SM */
                   KIND2 *pk2;
                   KIND3 *pk3;
               } u;
    /* 0x08 */ void *pvState;    /* the playing ASEGA / SMA, or the guard's player */
    /* 0x0c */ int grf;          /* the ApplyAseg flags */
} KINDE;

#endif
