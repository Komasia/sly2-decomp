/* UpdateSwXps: the boxes recomputed (dirty list 1) and the sweep lists sorted; then each moved attachment (dirty list 2,
 * flag 0x10 while done) and each of its overlap partners gets new contacts (PxpMarkOxaContacts; both objects told by vt
 * slot 54 and woken unless still when there were or are contacts); the moved ones leave dirty list 2 with their internal
 * contacts freed (vt slots 54 / 59), and every marked attachment's object gets vt slot 58. Layout: SafeHouse port
 * (so.h OX / OXA / PHYSW, bbmark.cpp). */
#include "so.h"
struct OXA;
struct OX { void *pxp; struct OX *poxNext; struct OX *poxOther; struct LO *psoOther; };   /* field: SafeHouse port */
struct SOX { char pad[0xEC]; struct OXA *poxa; };   /* the SO's attachment (+0xEC) */
struct OXA { char pad[0x58]; struct OXA *poxaNextDirty2; int x5C; struct LO *pso; struct OX *pox; void *pxpInternal; int pxpSensor; unsigned long grf; };   /* field: SafeHouse port */
struct SW { char pad[0x3D34]; struct OXA *poxaDirty2First; };   /* field: SafeHouse port (PHYSW apoxaDirty2) */
struct STACKSCOPE { int a[4]; };
void FlushSwOxaDirty1__FP2SW(struct SW *psw);
void UpdateSwAaox__FP2SW(struct SW *psw);
struct STACKSCOPE *__10STACKSCOPE(struct STACKSCOPE *);
void _$_10STACKSCOPE(struct STACKSCOPE *, int);
void FreeSwXpList(struct SW *, void *) asm("FreeSwXpList__FP2SWP2XP");
void *PxpMarkOxaContacts__FP3OXAT0P2SO(struct SW *, struct OXA *, struct OXA *);
void WakeAlo__FP3ALO(struct LO *);
void RemoveDlEntry__FP2DLPv(void *, struct OXA *);
#define VCALL(po, n, T) ((T)(po)->pvt[n].pfn)(VT_THIS((po), &(po)->pvt[n])
// name: SafeHouse port (UpdateSwXps)
void UpdateSwXps__FP2SW(struct SW *psw)
{
    struct STACKSCOPE ctx;
    struct OXA *apoxaMarked[0x300];
    int cpoxaMarked = 0;
    struct OXA *poxa;
    int i;
    FlushSwOxaDirty1__FP2SW(psw);
    UpdateSwAaox__FP2SW(psw);
    __10STACKSCOPE(&ctx);
    for (poxa = psw->poxaDirty2First; poxa; poxa = poxa->poxaNextDirty2) {
        unsigned long grf = poxa->grf;
        struct OX *pox;
        if (grf & 4)
            continue;
        grf |= 0x10;
        poxa->grf = grf;
        if (!(grf & 8)) {
            poxa->grf = grf | 8;
            apoxaMarked[cpoxaMarked++] = poxa;
        }
        for (pox = poxa->pox; pox; pox = pox->poxNext) {
            struct OXA *poxaOther = ((struct SOX *)pox->psoOther)->poxa;
            unsigned long grfOther = poxaOther->grf;
            void *pxpOld;
            if (grfOther & 0x10)
                continue;
            if (grfOther & 4)
                continue;
            if (!(grfOther & 8)) {
                poxaOther->grf = grfOther | 8;
                apoxaMarked[cpoxaMarked++] = poxaOther;
            }
            VCALL(poxa->pso, 54, void (*)(void *, struct LO *)), poxaOther->pso);
            VCALL(poxaOther->pso, 54, void (*)(void *, struct LO *)), poxa->pso);
            pxpOld = pox->pxp;
            FreeSwXpList(psw, pxpOld);
            { void *pvNew = PxpMarkOxaContacts__FP3OXAT0P2SO(psw, poxa, poxaOther); pox->pxp = pvNew; pox->poxOther->pxp = pvNew; }
            if (pxpOld || pox->pxp) {
                if (!VCALL(poxa->pso, 62, int (*)(void *))))
                    WakeAlo__FP3ALO(poxa->pso);
                if (!VCALL(poxaOther->pso, 62, int (*)(void *))))
                    WakeAlo__FP3ALO(poxaOther->pso);
            }
        }
    }
    for (poxa = psw->poxaDirty2First; poxa; poxa = psw->poxaDirty2First) {
        poxa->grf &= ~0x10L;
        VCALL(poxa->pso, 54, void (*)(void *, struct LO *)), 0);
        FreeSwXpList(psw, poxa->pxpInternal);
        poxa->pxpInternal = 0;
        VCALL(poxa->pso, 59, void (*)(void *)));
        poxa->grf &= ~2L;
        RemoveDlEntry__FP2DLPv(&psw->poxaDirty2First, poxa);
    }
    for (i = 0; i < cpoxaMarked; i++) {
        poxa = apoxaMarked[i];
        poxa->grf &= ~8L;
        VCALL(poxa->pso, 58, void (*)(void *)));
    }
    _$_10STACKSCOPE(&ctx, 2);
}
