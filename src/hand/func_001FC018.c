#include "vtbl.h"
struct VT { VTENT a[9]; };
struct P { char pad[0xC]; struct VT *pvt; };
void SetDirty__4CSndUiUi(struct P *, int, int);
// name: SafeHouse port (CSndPlain::OnAudible)
void OnAudible__9CSndPlaini(struct P *p, int f)
{
    if (!f) ((void (*)(void *))p->pvt->a[7].pfn)(VT_THIS(p, &p->pvt->a[7]));
    else {
        int n = 0x1FF;
        SetDirty__4CSndUiUi(p, ((int (*)(void *))p->pvt->a[8].pfn)(VT_THIS(p, &p->pvt->a[8])) == 2 ? n : 0x3FF, 8);
    }
}
