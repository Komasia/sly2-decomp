#include "cid.h"
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct O { int x0, x4, x8; VTENT *vt; char pad[0x13D0 - 0x10]; int x13D0; };
struct S { void *p0; char pad[0xC]; struct O *po; char pad1[0x1C]; qword q30; char pad2[0xB0]; qword qF0; char pad3[0x2C]; struct O *p12C; };
extern struct O *D_002DD5BC;
void SetBentleyCarried__FP7BENTLEYi(struct O *po, int n);
void ReparentBooty__FP3ALOii(struct O *po, int a, int b);
void SetAloCnstrLin__FP3ALOi(struct O *po, int a);
void SetAloCnstrAng__FP3ALOi(struct O *po, int a);
qword ConvertVec__FP2LOT0G9VU_VECTOR(void *p, int a, qword q);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *po, int n);
// name: SafeHouse port (ReleaseJtThrow)
void ReleaseJtThrow__FP7JTTHROW(struct S *p)
{
    struct O *po;
    if (p->po == D_002DD5BC) {
        if (p->po->x13D0 != 8) goto tail;
        SetBentleyCarried__FP7BENTLEYi(p->po, 1);
    } else {
        ReparentBooty__FP3ALOii(p->po, 0, 3);
        SetAloCnstrLin__FP3ALOi(p->po, 0);
        SetAloCnstrAng__FP3ALOi(p->po, 0);
    }
    ((void (*)())p->po->vt[35].pfn)(VT_THIS(p->po, &p->po->vt[35]), p->qF0);
    {
        VTENT *pve;
        po = p->po;
        pve = &po->vt[36];
        po = (struct O *)VT_THIS(po, pve);
        ((void (*)())pve->pfn)(po, ConvertVec__FP2LOT0G9VU_VECTOR(p->p0, 0, p->q30));
    }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p->po, CID_CARRY))
        ((void (*)())p->po->vt[76].pfn)(VT_THIS(p->po, &p->po->vt[76]), 1);
tail:
    if (p->p12C)
        ((void (*)())p->p12C->vt[9].pfn)(VT_THIS(p->p12C, &p->p12C->vt[9]));
}
