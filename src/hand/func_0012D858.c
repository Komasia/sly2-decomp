#include "vtbl.h"
typedef struct O { int pad[6]; VTENT *vt; } O;
typedef struct T { int pad[4]; O *p; int pad2[2]; O *q; } T;
// name: SafeHouse port (CTRLSOURCE::Start)
void Start__10CTRLSOURCE(T *t)
{
    O *p = t->p;
    t->q = p;
    if (p)
        ((void (*)(void *))p->vt[1].pfn)(VT_THIS(p, &p->vt[1]));
}
