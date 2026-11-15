/* func_001A6D28 (0x1A6D28): sets a value on an LO and its ancestors: requeues the root (its LOROOT +0x14,
 * whose LO is in the world) for its activation check, calls vtable entry 46 with it, and ORs it into byte +0x2D of
 * each of its ancestors (the +0x10 parent links). */
#include "vtbl.h"
struct ALO {
    char pad[0x28];
    unsigned long b0 : 52;
    long n52 : 4;
    unsigned int b56 : 4;
    unsigned int fInWorld : 1;
};
struct LOROOT { struct ALO *plo; };
struct O {
    char pad[0xC];
    VTENT *vt;
    struct O *pNext;
    struct LOROOT *ploroot;
    char pad2[0x15];
    unsigned char b2D;
};
extern char g_sw[];
void QueueLoRoot__FP2SWP2LO(void *, void *);
void func_001A6D28(struct O *plo, int b)
{
    struct O *ploAncestor;
    if (plo->ploroot->plo->fInWorld)
        QueueLoRoot__FP2SWP2LO(g_sw, plo->ploroot);
    {
        VTENT *e = &plo->vt[46];
        ((void (*)(void *, int))e->pfn)(VT_THIS(plo, e), b);
    }
    for (ploAncestor = plo->pNext; ploAncestor; ploAncestor = ploAncestor->pNext)
        ploAncestor->b2D |= b;
}
