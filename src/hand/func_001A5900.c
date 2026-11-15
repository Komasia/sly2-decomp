/* func_001A5900 (0x1A5900): LO vt slot 10, SetLoParent: moves the LO under a new parent (null: a root). It is in the
 * world afterwards when the new parent is (or it is a root) and it is not removed. It leaves its old sibling list for
 * the new one (removed LOs at the end), leaves the update table and the active roots if active, gets the new parent,
 * slot 13 tells it (new, old parent), its children (slot 28) follow (slot 10), OnAdd / OnRemove (11 / 12) when the
 * in-world state changed, then it rejoins the update table if active, else a new root's activation is checked.
 * SafeHouse brx.cpp / activate.cpp. */
/* (match note) parent bit via (int)(x>>60)&1, fNew via if(!(bit56)) fNew=1; else fNew=0; (gives addiu/movn). */
#include "vtbl.h"
typedef struct ALO ALO;
struct ALO { int x0, x4, x8; VTENT *vt; ALO *x10; ALO **x14; char pad[0x24 - 0x18]; ALO *x24; union { unsigned long u; struct { unsigned long f0 : 56; unsigned long f56 : 1; unsigned long f57 : 3; unsigned long f60 : 1; unsigned long f61 : 3; } b; } x28; };
#define VFN(p, n, T) ((T)(p)->vt[n].pfn)
#define VTHIS(p, n) ((ALO *)VT_THIS((p), &(p)->vt[n]))
#define GRFLO_REMOVED 0x0100000000000000UL  /* LO +0x28 bit 56 */
#define VT_SET_PARENT 10
#define VT_ON_ADD 11
#define VT_ON_REMOVE 12
#define VT_PARENT_CHANGED 13
#define VT_REMOVE_FROM_UPDATE 22
#define VT_ADD_TO_UPDATE 23
#define VT_CHILDREN 28
extern char g_dlActiveRoots[] __asm__("D_003DD4BC");
extern char g_sw[];
void func_001A5448(ALO *paloParent, void **ppdl, ALO ***pppaloFirstRemoved);
void RemoveDlEntry__FP2DLPv(void *pdl, void *p);
void AppendDlEntry__FP2DLPv(void *pdl, void *p);
void InsertDlEntryBefore__FP2DLPvT1(void *pdl, void *pBefore, void *p);
int FLoActive__FP2LO(ALO *p);
void CheckLoRoot__FP2SWP2LO(void *g, ALO *p);
void func_001A5900(ALO *palo, ALO *paloParent, int n1, int n2)
{
    unsigned long fOld = palo->x28.u >> 60 & 1;
    unsigned long fNew = 0;
    void *pdlOld;
    ALO **ppaloOld;
    void *pdlNew;
    ALO **ppaloNew;
    ALO *paloOld;
    ALO **apaloChild;
    int cpaloChild, i;
    if (!paloParent || ((int)(paloParent->x28.u >> 60) & 1)) {
        if (!(palo->x28.u & GRFLO_REMOVED)) fNew = 1; else fNew = 0;
    }
    func_001A5448(palo->x10, &pdlOld, &ppaloOld);
    func_001A5448(paloParent, &pdlNew, &ppaloNew);
    if (palo->x28.u & GRFLO_REMOVED) {
        if (palo == *ppaloOld)
            *ppaloOld = palo->x24;
        RemoveDlEntry__FP2DLPv(pdlOld, palo);
        AppendDlEntry__FP2DLPv(pdlNew, palo);
        if (!*ppaloNew)
            *ppaloNew = palo;
    } else {
        RemoveDlEntry__FP2DLPv(pdlOld, palo);
        InsertDlEntryBefore__FP2DLPvT1(pdlNew, *ppaloNew, palo);
    }
    if (FLoActive__FP2LO(palo)) {
        VFN(palo, VT_REMOVE_FROM_UPDATE, void (*)(ALO *))(VTHIS(palo, VT_REMOVE_FROM_UPDATE));
        if (*palo->x14 == palo)
            RemoveDlEntry__FP2DLPv(g_dlActiveRoots, palo->x14);
    }
    paloOld = palo->x10;
    palo->x10 = paloParent;
    VFN(palo, VT_PARENT_CHANGED, void (*)(ALO *, ALO *, ALO *))(VTHIS(palo, VT_PARENT_CHANGED), palo, paloOld);
    cpaloChild = VFN(palo, VT_CHILDREN, int (*)(ALO *, ALO ***))(VTHIS(palo, VT_CHILDREN), &apaloChild);
    for (i = 0; i < cpaloChild; i++) {
        ALO *paloChild = apaloChild[i];
        VFN(paloChild, VT_SET_PARENT, void (*)(ALO *, ALO *, int, int))(VTHIS(paloChild, VT_SET_PARENT), paloParent, n1, n2);
    }
    if (fNew != fOld) {
        if (fNew)
            VFN(palo, VT_ON_ADD, void (*)(ALO *))(VTHIS(palo, VT_ON_ADD));
        else
            VFN(palo, VT_ON_REMOVE, void (*)(ALO *))(VTHIS(palo, VT_ON_REMOVE));
    }
    if (FLoActive__FP2LO(palo))
        VFN(palo, VT_ADD_TO_UPDATE, void (*)(ALO *))(VTHIS(palo, VT_ADD_TO_UPDATE));
    else if (!palo->x10 && fNew)
        CheckLoRoot__FP2SWP2LO(g_sw, palo);
}
