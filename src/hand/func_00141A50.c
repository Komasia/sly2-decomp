/* UpdateActorAbilities: each of the three button slots: idle, a press (within 0.15 s) starts its ability when allowed
 * (vt slot 99) and affordable (the table's power cost; else a refusal sound, and the time noted), into the ability's
 * first state; held, it runs (vt slot 101) until its button is let go or it is no longer allowed. SafeHouse port
 * (gadget.h). */
#include "vtbl.h"
struct ABSLOT { int id; int state; int x; };   /* a button's ability slot (SafeHouse gadget.h) */
struct PADCTL { char pad[0x30]; int grfbtnHeld; };
struct ABILITYDEF { int stateStart; int x4; int x8; int mpCost; char pad[0x10]; };   /* the abilities' table */
struct ACTOR {
    char pad[0xC]; VTENT *vt; char pad1[0x150 - 0x10]; struct PADCTL *ppadctl; char pad2[0x1180 - 0x154];
    struct ABSLOT aabslot[3]; char pad3[0x1304 - 0x11A4]; float tPowerSpent;
};
#include "clock.h"
extern int D_002C3258[];
extern struct ABILITYDEF D_002BCD00[];
int GrfPadctlTakePressed__FP6PADCTL(struct PADCTL *pactor, int mask, float g);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *pactor, int n);
int NActorPower__FP5ACTOR(struct ACTOR *pactor);
void SetAbilityState__FP5ACTORP6ABSLOTi(struct ACTOR *pactor, struct ABSLOT *pabslot, int n);
// name: SafeHouse port (gadget.h UpdateActorAbilities, orig 0x141A50)
void UpdateActorAbilities__FP5ACTOR(struct ACTOR *pactor)
{
    int i;
    int *pmask;
    if (!pactor->ppadctl) return;
    i = 0;
    pmask = D_002C3258;
    do {
        int mask = *pmask;
        struct ABSLOT *pabslot = &pactor->aabslot[i];
        int id = pabslot->id;
        switch (pabslot->state) {
        case 0:
            if (GrfPadctlTakePressed__FP6PADCTL(pactor->ppadctl, mask, 0.15f)) {
                if (!((int (*)(void *, ...))pactor->vt[99].pfn)(VT_THIS(pactor, &pactor->vt[99]), id)) {
                    SetSource__4CSndPv(PsndNewPlain__Fi(0x2E), 0);
                } else {
                    int n = NActorPower__FP5ACTOR(pactor);
                    if (n < D_002BCD00[id].mpCost) {
                        SetSource__4CSndPv(PsndNewPlain__Fi(0x2E), 0);
                        pactor->tPowerSpent = g_clock.t;
                    } else {
                        SetAbilityState__FP5ACTORP6ABSLOTi(pactor, pabslot, D_002BCD00[id].stateStart);
                    }
                }
            }
            break;
        case 1:
            if (!(pactor->ppadctl->grfbtnHeld & mask) || !((int (*)(void *, int))pactor->vt[99].pfn)(VT_THIS(pactor, &pactor->vt[99]), id))
                SetAbilityState__FP5ACTORP6ABSLOTi(pactor, pabslot, 0);
            else
                ((void (*)(void *, struct ABSLOT *))pactor->vt[101].pfn)(VT_THIS(pactor, &pactor->vt[101]), pabslot);
            break;
        }
        pmask++;
    } while (++i < 3);
}
