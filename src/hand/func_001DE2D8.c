/* LaserOverlapKind (vt slot 61): how the laser overlaps palo: 2 (overlap) if palo matches one of the laser's
 * listed object ids or derives from one of its listed classes, else 1. */
#include "h3_laser.h"
#define OVERLAPK_Nothing 1
#define OVERLAPK_Overlap 2

typedef struct LASER {
    /* 0x000 */ char unk_so[0x150];   /* the SO base */
    /* 0x150 */ int coid;
    /* 0x154 */ int aoid[COID_LASER_MAX];
    /* 0x170 */ int ccid;
    /* 0x174 */ int acid[COID_LASER_MAX];
} LASER;
int func_001A6290(void *palo, int oid);      /* palo's oid is oid, or one of its alias entries has it */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
int func_00134310(int overlapk, int overlapkOther);   /* the larger of two overlap kinds */
// name: SafeHouse port (LaserOverlapKind)
int LaserOverlapKind__FP3ALOT0(LASER *plaser, void *palo)
{
    int ioid, icid;
    int overlapk = OVERLAPK_Nothing;
    for (ioid = 0; ioid < plaser->coid; ioid++) {
        if (func_001A6290(palo, plaser->aoid[ioid]))
            overlapk = func_00134310(overlapk, OVERLAPK_Overlap);
    }
    for (icid = 0; icid < plaser->ccid; icid++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(palo, plaser->acid[icid]))
            overlapk = func_00134310(overlapk, OVERLAPK_Overlap);
    }
    return overlapk;
}
