/* The actor's script runner (+0x1084, SafeHouse scpt.cpp): the old one released (vt slot 2; a pose interaction ended,
 * vt slot 88), the new one held (vt slot 1), the AI jobs cleared, the binoculars closed, and a throw ended unless the
 * runner is in state 0x1E. Layout: SafeHouse port (actor.h prunScript, stThrow). */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; char pad2[0x40 - 0x10]; int *pnState; };
struct ACTOR {
    char pad[0xC]; VTENT *vt; char pad1[0x26C - 0x10]; char jobs[0x4C8 - 0x26C]; int n4C8;
    char pad2[0xF00 - 0x4CC]; char binoc[0x1084 - 0xF00]; struct LO *prunScript; char pad3[0x11B4 - 0x1088]; int stThrow;
};
void ClearJobs__FP5ACTOR(void *pactor);
int func_001443D8(struct ACTOR *pactor);
void SetBinocState__FP5ACTORi(void *pactor, int n);
void func_00143DE8(struct ACTOR *pactor, struct LO *prun)
{
    struct LO *prunOld = pactor->prunScript;
    if (prun == prunOld) return;
    if (prunOld) {
        ((void (*)(void *, ...))prunOld->vt[2].pfn)(VT_THIS(prunOld, &prunOld->vt[2]));
        switch (pactor->n4C8) {
        case 5: case 6:
            ((void (*)(void *, ...))pactor->vt[88].pfn)(VT_THIS(pactor, &pactor->vt[88]), 0);
            break;
        }
    }
    pactor->prunScript = prun;
    if (prun) {
        ((void (*)(void *, ...))prun->vt[1].pfn)(VT_THIS(prun, &prun->vt[1]));
        ClearJobs__FP5ACTOR(pactor->jobs);
        if (func_001443D8(pactor)) SetBinocState__FP5ACTORi(pactor->binoc, -1);
        if (pactor->stThrow != -1 && *pactor->prunScript->pnState != 0x1E)
            ((void (*)(void *, ...))pactor->vt[88].pfn)(VT_THIS(pactor, &pactor->vt[88]), 0);
    }
}
