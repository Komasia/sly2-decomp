/* PxpAddSw (0x1A7C18): adds a contact between two geometry entries to the world: a new XP from the world's slot heap
 * (SW +0x3D40) with end 0 at pos and end 1 at pos - normal * gDist; each end records its entry, the entry's
 * transform and owner and the owner's attachment root, and its point in the transform's frame; the kind and its two
 * tags, the default friction / elasticity (D_002BFD30 / D_002BFD34); each owner is told (vtable entry 55, with the
 * end's index), the contact's movement is computed (RecalcSwXpMovement) and it is put at the head of *ppxp.
 * SafeHouse so.cpp. */
#include "vtbl.h"
#include "h5_xp.h"
typedef union { qword q; float f[4]; } U;
struct SUB { char pad[0x60]; void *x60; };
struct LO { int x0, x4, x8; VTENT *vt; char pad[0xEC - 0x10]; struct SUB *xEC; };
struct SOE { struct XF *pxf; struct LO *palo; };
struct SW { char pad[0x3D40]; char slotheapXp[1]; };
#define VT_ADD_XP 55
extern float g_muDefault __asm__("D_002BFD30");
extern float g_elasDefault __asm__("D_002BFD34");
struct XP *func_0011CCC0(void *pslotheap);
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int pxfFrom, void *pxfTo, qword pos);
void RecalcSwXpMovement__FP2SWiPP2XP(struct SW *psw, int cpxp, struct XP **apxp);
// name: SafeHouse port (PxpAddSw)
void PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(struct SW *psw, struct SOE *psoe0, struct SOE *psoe1, qword pos, qword normal, int xpk, int nTag0, int nTag1, struct XP **ppxp, float gDist)
{
    U u;
    struct XP *pxp;
    int i;
    struct XPD *pxpd;
    struct XP *pxpNew;
    pxp = pxpNew = func_0011CCC0(psw->slotheapXp);
    pxpNew->axpd[0].pos = pos;
    {
        qword s, r;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(-gDist));
        u.q = s;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(pos), "j"(normal), "j"(s));
        pxpNew->axpd[1].pos = r;
    }
    pxpNew->normal = normal;
    for (i = 0; i < 2; i++) {
        pxpd = &pxp->axpd[i];
        if (i == 0)
            pxpd->psoe = psoe0;
        else
            pxpd->psoe = psoe1;
        if (pxpd->psoe) {
            pxpd->pxf = pxpd->psoe->pxf;
            pxpd->palo = (struct ALO *)pxpd->psoe->palo;
            pxpd->paloRoot = ((struct LO *)pxpd->palo)->xEC->x60;
        }
        pxpd->posLocal = PosConvertXfs__FP2XFT0G9VU_VECTOR(0, pxpd->pxf, pxpd->pos);
    }
    pxp->gDist = gDist;
    pxp->xpk = xpk;
    pxp->mu = g_muDefault;
    pxp->elas = g_elasDefault;
    pxp->nTag0 = nTag0;
    pxp->nTag1 = nTag1;
    for (i = 0; i < 2; i++) {
        struct LO *plo;
        pxpd = &pxp->axpd[i];
        plo = (struct LO *)pxpd->palo;
        if (plo)
            ((void (*)(struct LO *, struct XP *, int))plo->vt[VT_ADD_XP].pfn)((struct LO *)VT_THIS(plo, &plo->vt[VT_ADD_XP]), pxp, i);
    }
    RecalcSwXpMovement__FP2SWiPP2XP(psw, 1, &pxp);
    {
        struct XP *pxpLast = pxp;
        while (pxpLast->pxpNext)
            pxpLast = pxpLast->pxpNext;
        pxpLast->pxpNext = *ppxp;
        *ppxp = pxp;
    }
}
