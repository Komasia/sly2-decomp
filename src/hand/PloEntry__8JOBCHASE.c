/* JOBCHASE::PloEntry: the object of the chase graph entry Carmelita is at / going to. Layout: SafeHouse port
 * (aichase.h JOBCHASE, CHASEGRAPH). */
#include "aijob.h"

struct LO;
struct CHASEENTRY {
    /* 0x0 */ int k;             /* field: SafeHouse port - 0 runs to it, 1 hops */
    /* 0x4 */ int oid;           /* field: SafeHouse port */
    /* 0x8 */ struct LO *plo;    /* field: SafeHouse port */
};
struct CHASEGRAPH {
    /* 0x00 */ char pad0[0x54];
    /* 0x54 */ int centry;
    /* 0x58 */ struct CHASEENTRY *aentry;   /* field: SafeHouse port */
};
struct JOBCHASE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                      /* field: SafeHouse port */
    /* 0x34 */ float tSt;                   /* field: SafeHouse port */
    /* 0x38 */ struct CHASEGRAPH *pgraph;   /* field: SafeHouse port */
    /* 0x3c */ int i;                       /* field: SafeHouse port - the entry she is at / going to */
};

// name: SafeHouse port (JOBCHASE::PloEntry)
struct LO *PloEntry__8JOBCHASE(struct JOBCHASE *pjob)
{
    return pjob->pgraph->aentry[pjob->i].plo;
}
