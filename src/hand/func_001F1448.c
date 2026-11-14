#include "vtbl.h"
struct VT { VTENT a[3]; };
struct X { char pad[0xC]; struct VT *pvt; };
void RetractSma__FP3SMA(struct X *);
struct X *func_001F0380(void *, int, int, int);
// name: SafeHouse port (ReplaceSmaHandle)
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *pv, int a, int b, int c, struct X **ppx)
{
    if (*ppx) {
        RetractSma__FP3SMA(*ppx);
        ((void (*)(void *))(*ppx)->pvt->a[2].pfn)(VT_THIS(*ppx, &(*ppx)->pvt->a[2]));
        *ppx = 0;
    }
    if (pv) {
        struct X *px = func_001F0380(pv, a, b, c);
        *ppx = px;
        ((void (*)(void *))px->pvt->a[1].pfn)(VT_THIS(px, &px->pvt->a[1]));
    }
}
