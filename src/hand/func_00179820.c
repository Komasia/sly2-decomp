/* JOBHIT2::Exit: JOBHIT's exit, then the guard's +0xFEC object removed again (its vt slot 9). */
#include "vtbl.h"
#include "h2_aijobs.h"

struct LOVT { char pad0[0xC]; VTENT *vt; };
struct GUARD {
    /* 0x000 */ char pad0[0xFEC];
    /* 0xfec */ struct LOVT *ploFEC;      /* field: SafeHouse port (option 331) */
};
void Exit__6JOBHIT(JOBHIT *pjob);

void func_00179820(JOBHIT *pjob)
{
    struct LOVT *plo;
    Exit__6JOBHIT(pjob);
    plo = pjob->jobmove.aijob.pguard->ploFEC;
    if (plo) { VTENT *pvte = &plo->vt[9]; ((void (*)(void *))pvte->pfn)(VT_THIS(plo, pvte)); }
}
