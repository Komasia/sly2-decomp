#include "vtbl.h"
typedef struct O { int pad[6]; VTENT *vt; } O;
typedef struct T { int pad[7]; O *q; } T;
// name: SafeHouse port (CTRLSOURCE::End)
void End__10CTRLSOURCE(T *t)
{
    O *p = t->q;
    if (p) {
        ((void (*)(void *))p->vt[2].pfn)(VT_THIS(p, &p->vt[2]));
        t->q = 0;
    }
}
