/* The object's splice event 6 (vt slot 3, no arguments; SafeHouse interactsplice.cpp: loader method 0x100860). */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
void func_00133380(struct LO *plo)
{
    VTENT *vt = plo->vt;
    ((void (*)(void *, int, int, int, int, int))vt[3].pfn)(VT_THIS(plo, &vt[3]), 6, 0, 0, 0, 0);
}
