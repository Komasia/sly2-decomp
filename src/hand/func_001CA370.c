#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
struct Z { VTENT *vt; };
struct R { int n; struct LO **ap; int x8; int c; int x10; int x14; void **ap18; char pad[0x6C - 0x1C]; };
struct G { char pad[0x3F08]; struct R *ar; };
void *func_001C9940(int i, int c);
void func_001CA370(struct G *pg, int i, int a, int b, void *x, int y, struct Z *pz)
{
    struct R *pr = &pg->ar[i];
    void *v = func_001C9940(i, pr->c);
    int j;
    pr->ap18[pr->c] = x;
    for (j = 0; j < pr->n; j++) {
        struct LO *plo = pr->ap[pr->c * pr->n + j];
        ((void (*)(void *, void *, int))plo->vt[25].pfn)(VT_THIS(plo, &plo->vt[25]), v, 1);
        ((void (*)(void *))plo->vt[8].pfn)(VT_THIS(plo, &plo->vt[8]));
        ((void (*)(void *, int, int, int))plo->vt[10].pfn)(VT_THIS(plo, &plo->vt[10]), a, b, 0);
        ((void (*)(void *, int))plo->vt[37].pfn)(VT_THIS(plo, &plo->vt[37]), y);
    }
    if (pz)
        ((void (*)(void *, int, struct LO **))pz->vt[1].pfn)(VT_THIS(pz, &pz->vt[1]), pr->n, &pr->ap[pr->c * pr->n]);
    pr->c++;
}
