/* *ppasega's reference (if any) released (vt slot 2) and the pointer cleared, without retracting it (SafeHouse
 * gang.cpp: after FAsegaRetracted, 0x1306A8). */
#include "vtbl.h"
struct ASEGA { int pad[3]; VTENT *vt; };
void func_001306A8(struct ASEGA **ppasega)
{
    struct ASEGA *pasega = *ppasega;
    if (pasega) {
        VTENT *vt = pasega->vt;
        ((void (*)(void *))vt[2].pfn)(VT_THIS(pasega, &vt[2]));
        *ppasega = 0;
    }
}
