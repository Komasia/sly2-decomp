#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { struct O *po; };
// name: SafeHouse port (HideSubtitleBox)
void HideSubtitleBox__FP9DIALOGSUB(struct S *p) { struct O *o = p->po; if (o) { VTENT *e = &o->vt[50]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); } }
