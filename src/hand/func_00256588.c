#include "vtbl.h"
typedef struct L { int x0; struct L *next; VTENT *vt; } L;
typedef struct O { char pad[0x28]; L *first; } O;

void func_00256588(O *p, void *pv)
{
    L *l;
    for (l = p->first; l; l = l->next)
        ((void (*)(void *, void *))l->vt[2].pfn)(VT_THIS(l, &l->vt[2]), pv);
}
