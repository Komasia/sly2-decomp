/* NActorPerceived: how the guards perceive the actor, by a test noise (+0x10C4) made at its place: 2 while it uses its
 * binoculars (0x1443D8), when no noise can be made or a guard is in state 0x1D / 0xB; 1 when a guard (vt slot 89) or
 * a listener (D_003E1468) hears it; else 0. The noise is removed after. Layout: SafeHouse port (actor.h ploNoise). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct SO { char pad[0xC]; VTENT *vt; char pad2[0xFE0 - 0x10]; struct SO *psoNext; };
struct X { char pad[0x104]; struct X *pxNext; };
struct ACTOR { char pad[0x10C4]; void *ploNoise; };
extern struct SO *D_003E1444;
extern struct X *D_003E1468;
int func_001443D8(struct ACTOR *pactor);
qword PosOfLo__FP2LO(struct ACTOR *pactor);
void *func_00156698(void *a, qword pos, struct ACTOR *pactor);
int FGuardState(struct SO *pso, int n) asm("FGuardState__FP5GUARDi");
int FListenerHearsNoise__FP2LOP5NOISE(struct X *px, void *q);
void RemoveNoise__FP5NOISE(void *q);
// name: SafeHouse port (NActorPerceived)
int NActorPerceived__FP5ACTOR(struct ACTOR *pactor)
{
    int unused[4];
    void *q;
    int r;
    struct SO *pso;
    struct X *px;
    if (func_001443D8(pactor)) return 2;
    q = 0;
    if (pactor->ploNoise) q = func_00156698(pactor->ploNoise, PosOfLo__FP2LO(pactor), pactor);
    if (!q) return 2;
    r = 0;
    pso = D_003E1444;
    for (;;) {
        if (!pso) break;
        if (FGuardState(pso, 0x1D) || FGuardState(pso, 0xB)) { r = 2; break; }
        if (((int (*)(void *, void *))pso->vt[89].pfn)(VT_THIS(pso, &pso->vt[89]), q)) { r = 1; break; }
        pso = pso->psoNext;
    }
    if (r == 0) {
        for (px = D_003E1468; px; px = px->pxNext)
            if (FListenerHearsNoise__FP2LOP5NOISE(px, q)) { r = 1; break; }
    }
    RemoveNoise__FP5NOISE(q);
    return r;
}
