#include "cid.h"
#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; char pad2[0x28 - 0x10]; unsigned long flPad : 60; unsigned int fBit60 : 1; char pad3[0xE0 - 0x30]; void *pvE0; };
struct G { int a; };
extern struct G g_sw;
struct P { char pad[0x24]; void *p24; char pad2[0x6C - 0x28]; struct O *po; int fActive; };
void SetZoneForced__FP2LOi(struct O *po, int n);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
void *func_001C4A48(struct G *pg);
void func_001E4F20(struct P *p, struct O *po)
{
    if (p->po) {
        SetZoneForced__FP2LOi(p->po, -1);
        p->po->pvE0 = 0;
        if (p->fActive) ((void (*)(void *))p->po->vt[9].pfn)(VT_THIS(p->po, &p->po->vt[9]));
        p->po = 0;
    }
    if (!po) return;
    p->po = po;
    p->fActive = !po->fBit60;
    if (p->fActive) ((void (*)(void *))po->vt[8].pfn)(VT_THIS(po, &po->vt[8]));
    po->pvE0 = (p->p24 && FIsBasicDerivedFrom__FP5BASIC3CID(p->p24, CID_SO)) ? p->p24 : func_001C4A48(&g_sw);
    SetZoneForced__FP2LOi(po, 1);
}
