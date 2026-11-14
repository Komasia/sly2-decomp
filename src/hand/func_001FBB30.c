#include "vtbl.h"
struct A { char pad[0xC]; VTENT *vt; };
void Stop__4CSndf(struct A *p, float g);
void SetDirty__4CSndUiUi(struct A *p, int a, int b);
void func_001FBB30(int f, long l)
{
    struct A *p = (struct A *)l;
    if (!f)
        Stop__4CSndf(p, 0.0f);
    else
        SetDirty__4CSndUiUi(p, 0x400, 0x400);
    ((void (*)(void *))p->vt[2].pfn)(VT_THIS(p, &p->vt[2]));
}
