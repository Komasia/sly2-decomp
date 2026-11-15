/* RemoveLo (0x1A5630): LO vt slot 9, takes an LO out of the world: if active it leaves the update table (slot 22; a root also the
 * active roots D_003DD4BC), a root is dequeued; it moves to the end of its sibling list (the first removed if none
 * was), gets its removed bit, its children are removed (slot 28 lists them, each one's slot 9), then its OnRemove
 * (slot 12) if it was in the world. SafeHouse activate.cpp, Sly 1 RemoveLo. */
#include "vtbl.h"
struct S { int x0, x4, x8; VTENT *vt; void *x10; int x14; char pad[0x10]; unsigned long x28; };
extern char g_dlActiveRoots[] __asm__("D_003DD4BC"), g_sw[];
#define GRFLO_REMOVED (1UL << 56)   /* LO +0x28 bit 56: removed from the world (SafeHouse fRemoved) */
#define GRFLO_IN_WORLD (1UL << 60)  /* bit 60: in the world (SafeHouse fInWorld) */
#define VT_ON_REMOVE (0x60 / 8)       /* slot 12 */
#define VT_REMOVE (0x48 / 8)          /* slot 9 */
#define VT_CHILDREN (0xE0 / 8)        /* slot 28: the children list */
#define VT_REMOVE_FROM_UPDATE (0xB0 / 8)  /* RemoveLoFromUpdateTable (0x1A6150) */
int FLoActive__FP2LO(struct S *s);
void RemoveDlEntry__FP2DLPv(void *a, void *b);
void DequeueLoRoot__FP2SWP2LO(void *a, int b);
void func_001A5448(void *p, void **a, struct S ***b);
void AppendDlEntry__FP2DLPv(void *a, struct S *s);
// name: SafeHouse port (LO vt slot 9, RemoveLo 0x1A5630) + Sly 1 RemoveLo
void RemoveLo(struct S *s) asm("RemoveLo__FP2LO");
void RemoveLo(struct S *plo)
{
    VTENT *e;
    unsigned long fInWorld;
    void *pdl;
    struct S **pploFirstRemoved;
    struct S **aploChild;
    int cploChild, i;
    if (plo->x28 & GRFLO_REMOVED)
        return;
    if (FLoActive__FP2LO(plo)) {
        e = &plo->vt[VT_REMOVE_FROM_UPDATE];
        ((void (*)(void *))e->pfn)(VT_THIS(plo, e));
        if (!plo->x10)
            RemoveDlEntry__FP2DLPv(g_dlActiveRoots, (void *)plo->x14);
    }
    if (!plo->x10)
        DequeueLoRoot__FP2SWP2LO(g_sw, plo->x14);
    fInWorld = (plo->x28 >> 60) & 1;
    func_001A5448(plo->x10, &pdl, &pploFirstRemoved);
    RemoveDlEntry__FP2DLPv(pdl, plo);
    AppendDlEntry__FP2DLPv(pdl, plo);
    if (!*pploFirstRemoved)
        *pploFirstRemoved = plo;
    plo->x28 |= GRFLO_REMOVED;
    e = &plo->vt[VT_CHILDREN];
    cploChild = ((int (*)(void *, struct S ***))e->pfn)(VT_THIS(plo, e), &aploChild);
    for (i = 0; i < cploChild; i++) {
        struct S *ploChild = aploChild[i];
        VTENT *g = &ploChild->vt[VT_REMOVE];
        ((void (*)(void *))g->pfn)(VT_THIS(ploChild, g));
    }
    if (fInWorld) {
        e = &plo->vt[VT_ON_REMOVE];
        ((void (*)(void *))e->pfn)(VT_THIS(plo, e));
    }
}
