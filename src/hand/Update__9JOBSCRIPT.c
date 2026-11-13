/* JOBSCRIPT::Update (AIJOB vt slot 10): the base update; then while the current command is done, on to the next
 * one (+0x18) and execute it (vt slot 15, JOBSCRIPT::SetState / Execute). Layout: SafeHouse port (aijobs.h
 * JOBSCRIPT). */
#include "aijob.h"
#include "vtbl.h"

struct CMD {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ struct CMD *pcmdNext;
};
struct JOBSCRIPT {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
    /* 0x10 */ char pad10[0x38 - 0x10];
    /* 0x38 */ struct CMD *pcmd;      /* field: SafeHouse port - the current command */
};
void Update__5AIJOB(struct JOBSCRIPT *pjob);
int FRunning__9JOBSCRIPT(struct JOBSCRIPT *pjob);

// name: SafeHouse port (JOBSCRIPT::Update)
void Update__9JOBSCRIPT(struct JOBSCRIPT *pjob)
{
    Update__5AIJOB(pjob);
    while (pjob->pcmd != 0) {
        struct CMD *pcmd;
        VTENT *pvte;
        if (FRunning__9JOBSCRIPT(pjob))
            return;
        pcmd = pjob->pcmd->pcmdNext;
        pjob->pcmd = pcmd;
        if (pcmd == 0)
            return;
        pvte = &pjob->pvt[0x78 / 8];
        ((void (*)(void *, struct CMD *))pvte->pfn)(VT_THIS(pjob, pvte), pcmd);
    }
}
