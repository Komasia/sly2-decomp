/* AddLo (0x1A5478): LO vt slot 8, puts a removed LO back in the world: clears its removed bit, moves it before its
 * parent's first removed child, calls its OnAdd (slot 11) when the parent is in the world (or it is a root), queues a
 * root whose activation kind is not 2, adds its children (slot 28 lists them, each one's slot 8), then if active it joins
 * the update table (slot 23), else checks a root's activation (CheckLoRoot). SafeHouse activate.cpp, Sly 1 AddLo. */
#include "vtbl.h"
struct S {
    int x0, x4, x8; VTENT *vt; struct S *x10; int x14; char pad[0xC]; struct S *x24;
    union { unsigned long u; struct { unsigned long f0 : 52; long st : 4; unsigned long f56 : 4; unsigned long f60 : 1; unsigned long f61 : 3; } b; } x28;
};
extern char g_sw[];
#define GRFLO_REMOVED (1UL << 56)   /* LO +0x28 bit 56: removed from the world (SafeHouse fRemoved) */
#define GRFLO_IN_WORLD (1UL << 60)  /* bit 60: in the world (SafeHouse fInWorld) */
#define VT_ON_ADD (0x58 / 8)          /* slot 11 */
#define VT_ADD (0x40 / 8)             /* slot 8 */
#define VT_CHILDREN (0xE0 / 8)        /* slot 28: the children list */
#define VT_ADD_TO_UPDATE (0xB8 / 8)   /* AddLoToUpdateTable (0x1A6178) */
void func_001A5448(struct S *p, void **a, struct S ***b);
void RemoveDlEntry__FP2DLPv(void *a, struct S *s);
void InsertDlEntryBefore__FP2DLPvT1(void *a, struct S *b, struct S *s);
void QueueLoRoot__FP2SWP2LO(void *g, int n);
int FLoActive__FP2LO(struct S *s);
void CheckLoRoot__FP2SWP2LO(void *g, struct S *s);
// name: SafeHouse port (LO vt slot 8, AddLo 0x1A5478) + Sly 1 AddLo
void AddLo(struct S *s) asm("AddLo__FP2LO");
void AddLo(struct S *plo)
{
    void *pdl;
    struct S **pploFirstRemoved;
    struct S **aploChild;
    VTENT *e;
    int cploChild, i;
    if (!(plo->x28.u & GRFLO_REMOVED))
        return;
    plo->x28.u &= ~GRFLO_REMOVED;
    func_001A5448(plo->x10, &pdl, &pploFirstRemoved);
    if (plo == *pploFirstRemoved) {
        *pploFirstRemoved = plo->x24;
    } else {
        RemoveDlEntry__FP2DLPv(pdl, plo);
        InsertDlEntryBefore__FP2DLPvT1(pdl, *pploFirstRemoved, plo);
    }
    if (plo->x10) {
        unsigned long t = (plo->x10->x28.u >> 60) & 1;
        if (!t)
            goto skip;
    }
    e = &plo->vt[VT_ON_ADD];
    ((void (*)(void *))e->pfn)(VT_THIS(plo, e));
skip:
    if (!plo->x10 && plo->x28.b.st != 2)
        QueueLoRoot__FP2SWP2LO(g_sw, plo->x14);
    e = &plo->vt[VT_CHILDREN];
    cploChild = ((int (*)(void *, struct S ***))e->pfn)(VT_THIS(plo, e), &aploChild);
    for (i = 0; i < cploChild; i++) {
        struct S *ploChild = aploChild[i];
        VTENT *g = &ploChild->vt[VT_ADD];
        ((void (*)(void *))g->pfn)(VT_THIS(ploChild, g));
    }
    if (FLoActive__FP2LO(plo)) {
        e = &plo->vt[VT_ADD_TO_UPDATE];
        ((void (*)(void *))e->pfn)(VT_THIS(plo, e));
    } else if (!plo->x10) {
        CheckLoRoot__FP2SWP2LO(g_sw, plo);
    }
}
