#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct O { int a[3]; VTENT *vt; };
struct P { int a; int b; float f; float g; qword q; qword r; qword s; };
void s1_memset(void *pv, int b, int cb) asm("memset");
void ExplodeExpl__FP4EXPL(struct O *o)
{
    struct P p = {0};
    VTENT *vt;

    vt = o->vt;
    ((void (*)())vt[51].pfn)(VT_THIS(o, &vt[51]), &p);
}
