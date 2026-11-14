#include "vtbl.h"
typedef struct O { int pad[6]; VTENT *vt; } O;
typedef struct T { int pad; void *a; void *b; int pad2; O *p; int pad3[2]; O *q; } T;
void InvalidateXfParams__FP3ALOP2XF(void *a, void *b);
// name: SafeHouse port (CTRLSOURCE::Refresh)
void Refresh__10CTRLSOURCE(T *t)
{
    O *p;
    if (t->q != t->p) {
        InvalidateXfParams__FP3ALOP2XF(t->a, t->b);
        p = t->q;
        if (p)
            ((void (*)(void *))p->vt[2].pfn)(VT_THIS(p, &p->vt[2]));
        p = t->p;
        t->q = p;
        if (p)
            ((void (*)(void *))p->vt[1].pfn)(VT_THIS(p, &p->vt[1]));
    }
}
