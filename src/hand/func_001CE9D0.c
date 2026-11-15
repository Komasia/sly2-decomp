#include "so.h"
struct N { struct LO *plo; int x4; struct N *pnNext; };
struct S { int x0; int cRef; char p1[0xE8 - 0x8]; struct N *pn; VTENT *vt; };
extern char D_003E1144[];
extern char D_003E14E4[];
void func_0011CD98(void *pool, void *pv);
void ReleaseRip__FP3RIP(struct S *p)
{
    struct N *pn, *pnNext;
    if (--p->cRef == 0) {
        ((void (*)(void *))p->vt[3].pfn)(VT_THIS(p, &p->vt[3]));
        for (pn = p->pn; pn; pn = pnNext) {
            struct LO *plo = pn->plo;
            ((void (*)(void *, int, struct S *))plo->pvt[5].pfn)(VT_THIS(plo, &plo->pvt[5]), 8, p);
            pnNext = pn->pnNext;
            func_0011CD98(D_003E1144, pn);
        }
        p->pn = 0;
        func_0011CD98(D_003E14E4, p);
    }
}
