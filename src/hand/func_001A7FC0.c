/* RecalcSwXpMovement (0x1A7FC0): updates contacts' velocities: each end on a transform gets its point's velocity
 * (VelXfPoint) and its owner is told (vtable entry 56, with the end's index); then each owner's entry 57; then the
 * relative velocity dv = vel0 - vel1. Field names: include/h5_xp.h (SafeHouse so.h XPD / XP). */
#include "so.h"
struct LO;
struct XP;
struct XPD { int psoe; void *pxf; int paloRoot; struct LO *palo; qword pos; qword posLocal; qword vel; };
struct XP { struct XPD axpd[2]; char pad[0x30]; qword dv; };
#define VT_XP_MOVED 56
#define VT_XP_MOVED2 57
qword VelXfPoint__FP2XFT0G9VU_VECTOR(void *pxf, int pxfRel, qword pos);
void RecalcSwXpMovement__FP2SWiPP2XP(void *psw, int cpxp, struct XP **apxp)
{
    int i;
    for (i = 0; i < cpxp; i++) {
        struct XP *pxp = apxp[i];
        struct XPD *pxpd;
        int j;
        pxpd = pxp->axpd;
        for (j = 0; j < 2; j++, pxpd++) {
            if (pxpd->pxf) {
                struct LO *palo;
                pxpd->vel = VelXfPoint__FP2XFT0G9VU_VECTOR(pxpd->pxf, 0, pxpd->pos);
                palo = pxpd->palo;
                ((void (*)(struct LO *, struct XP *, int))palo->pvt[VT_XP_MOVED].pfn)((struct LO *)VT_THIS(palo, &palo->pvt[VT_XP_MOVED]), pxp, j);
            }
        }
        for (j = 0; j < 2; j++) {
            struct LO *palo = pxp->axpd[j].palo;
            if (palo)
                ((void (*)(struct LO *, struct XP *, int))palo->pvt[VT_XP_MOVED2].pfn)((struct LO *)VT_THIS(palo, &palo->pvt[VT_XP_MOVED2]), pxp, j);
        }
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(pxp->dv) : "j"(pxp->axpd[0].vel), "j"(pxp->axpd[1].vel));
    }
}
