#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; };
#define VT(p, n, T) ((T)(p)->vt[n].pfn)
struct REQUEST { int value; int *pointer; };
void func_00206820(struct S *p)
{
    struct REQUEST request;
    register VTENT *initialTable __asm__("$3");
    request.pointer=&request.value;
    initialTable=p->vt;
    request.value=0;
    ((void (*)(void*,int))initialTable[27].pfn)(VT_THIS(p, &initialTable[27]),0);
    VT(p, 3, void (*)(void *, int, int, int, int **, int))(VT_THIS(p, &p->vt[3]), 0xF, 0, 1, &request.pointer, 0);
    VT(p, 26, void (*)(void *, int))(VT_THIS(p, &p->vt[26]), 0);
    VT(p, 3, void (*)(void *, int, int, int, int **, int))(VT_THIS(p, &p->vt[3]), 0xE, 0, 1, &request.pointer, 0);
}
