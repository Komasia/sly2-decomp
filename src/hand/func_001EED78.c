#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct L { int x; int c; struct O *ap[1]; };
// name: SafeHouse port (OfferJobMessage)
void OfferJobMessage__FP5GUARDii(struct L *pl, int a, int b)
{
    int i = pl->c;
    while (--i >= 0) {
        struct O *po = pl->ap[i];
        VTENT *e = &po->vt[13];
        if (((int (*)())e->pfn)(VT_THIS(po, e), a, b))
            break;
    }
}
