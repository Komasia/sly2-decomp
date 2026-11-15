/* StartPlayerCounters: the actor's health and power counters bound to its progress slots (D_002A4E18 / D_002A4E20 of its
 * progress node, vt slot 103); new ones (health 0) or fReset fill them (health +0xDFC, power +0x1300). Layout:
 * include/actor.h pnPower / nPowerMax. */
#include "vtbl.h"
struct P { char pad[0xC]; VTENT *vt; char pad2[0xDFC - 0x10]; int nHealthMax; int *pnHealth; char pad3[0x12FC - 0xE04]; int *pnPower; int nPowerMax; int pad4; int n1308; };
extern char D_002A4E18[];
extern char D_002A4E20[];
int *PnProgressSlot__FPvi(void *pactor, char *name, int n);
void func_00144188(struct P *pactor, int n);
void SetActorPower__FP5ACTORi(struct P *pactor, int n);
// name: SafeHouse port (StartPlayerCounters)
void StartPlayerCounters__FP5ACTORi(struct P *pactor, int fReset)
{
    VTENT *e = &pactor->vt[103];
    pactor->pnHealth = PnProgressSlot__FPvi(((void *(*)(void *))e->pfn)(VT_THIS(pactor, e)), D_002A4E18, 0);
    {
        VTENT *e2 = &pactor->vt[103];
        pactor->pnPower = PnProgressSlot__FPvi(((void *(*)(void *))e2->pfn)(VT_THIS(pactor, e2)), D_002A4E20, 0);
    }
    if (*pactor->pnHealth == 0 || fReset) {
        func_00144188(pactor, pactor->nHealthMax);
        SetActorPower__FP5ACTORi(pactor, pactor->nPowerMax);
        pactor->n1308 = 0;
    }
}
