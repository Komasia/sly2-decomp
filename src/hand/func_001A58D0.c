/* ReparentBooty (0x1A58D0): moves an object under a new parent through its vt slot 10 (SetLoParent) with
 * (paloParent, 0, n): brx.cpp's 0x1A58D0(po, 0, 0) makes a shared object a root. */
#include "vtbl.h"
#define VT_SET_PARENT 10
struct O { char pad[0xC]; VTENT *vt; };
// name: SafeHouse port (ReparentBooty)
void ReparentBooty__FP3ALOii(struct O *palo, int paloParent, int n) { VTENT *e = &palo->vt[VT_SET_PARENT]; ((void (*)(void *, int, int, int))e->pfn)(VT_THIS(palo, e), paloParent, 0, n); }
