/* JOBHIT2::Enter: the hit's entry from the guard's first kind array (+0x8D0) by the hit's kind, then JOBHIT's enter,
 * the tasks' event 0x15 (guard hit), the hit's source marked lost in the detector, and the guard's +0xFEC object added
 * to the world while the hit lasts (its vt slot 8; JOBHIT2::Exit removes it, slot 9). */
#include "vtbl.h"
#include "h2_aijobs.h"

struct SW;
struct DETECTOR;
extern struct SW g_game;
struct KINDE { int k; void *pv; void *pvState; int grf; };   /* field: SafeHouse port (guard.h KINDE) */
struct LOVT { char pad0[0xC]; VTENT *vt; };
struct GUARD {
    /* 0x000 */ char pad0[0x8D0];
    /* 0x8d0 */ struct KINDE akinde[26];  /* field: SafeHouse port (aakinde[0]) - by the hit kind's bit */
    /* 0xa70 */ char padA70[0xF64 - 0xA70];
    /* 0xf64 */ struct DETECTOR *pdet;    /* field: SafeHouse port */
    /* 0xf68 */ char padF68[0xFEC - 0xF68];
    /* 0xfec */ struct LOVT *ploFEC;      /* field: SafeHouse port (option 331) */
};
int IbitLow__FUi(unsigned int grf);
void Enter__6JOBHIT(JOBHIT *pjob);
void BroadcastTaskEvent__FP2SWiP2LO(struct SW *psw, int nEvent, struct GUARD *pguard);
void func_00154038(struct DETECTOR *pdet, struct LO *plo, int st);

// name: SafeHouse port (JOBHIT2::Enter)
void Enter__7JOBHIT2(JOBHIT *pjob)
{
    pjob->jobmove.pkinde = &pjob->jobmove.aijob.pguard->akinde[IbitLow__FUi(pjob->grfKind)];
    if (pjob->jobmove.pkinde->k == -1) pjob->jobmove.pkinde = 0;
    Enter__6JOBHIT(pjob);
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x15, pjob->jobmove.aijob.pguard);
    func_00154038(pjob->jobmove.aijob.pguard->pdet, pjob->psource, 2);
    {
        struct LOVT *plo = pjob->jobmove.aijob.pguard->ploFEC;
        if (plo) { VTENT *pvte = &plo->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(plo, pvte)); }
    }
}
