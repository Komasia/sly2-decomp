#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; void *p10; };
struct S { struct O *pNew; int a, b; struct O *pCur; };
extern char g_joy[];
void func_001D95B8(struct S *p) {
    struct O *po = p->pNew;
    struct O *pOld;
    if (po == p->pCur) return;
    if (p->pCur) {
        p->pCur->p10 = 0;
        {
            struct O *pc = p->pCur;
            VTENT *e = &pc->vt[9];
            ((void (*)(void *, int, struct O *))e->pfn)(VT_THIS(pc, e), 0, po);
        }
    }
    pOld = p->pCur;
    p->pCur = po;
    if (po) {
        VTENT *e = &po->vt[9];
        po->p10 = g_joy;
        ((void (*)(void *, int, struct O *))e->pfn)(VT_THIS(po, e), 1, pOld);
    }
}
