/* func_0020A100 (0x20A100, via 0x103F40): sets the guard's station - +0xF68 the object, +0xF70 the
 * point in its frame; a running station job (0x9C) in state 16 gets them too). */
#include "stepguard.h"
struct LO;
struct JOBSTATIONREC {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ struct LO *plo;
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ qword pos;
};
struct JOB9C {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ struct JOBSTATIONREC *prec;
    /* 0x1c */ char pad1c[0x30 - 0x1c];
    /* 0x30 */ int st;
};
struct JOB9C *PjobFind__FP5GUARDPv(void *pbhvstk, int cid);

void func_0020A100(struct GUARD *pguard, struct LO *plo, qword pos)
{
    struct JOB9C *pjob;
    pguard->ploStation = plo;
    pguard->posStation = pos;
    pjob = PjobFind__FP5GUARDPv(pguard->step.bhvstk, 0x9C);
    if (pjob != 0) {
        struct LO *ploStation = pguard->ploStation;
        if (ploStation != 0 && pjob->st == 0x10) {
            struct JOBSTATIONREC *prec = pjob->prec;
            prec->plo = ploStation;
            prec->pos = pguard->posStation;
        }
    }
}
