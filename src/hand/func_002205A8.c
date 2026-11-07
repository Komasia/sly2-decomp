typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int x0, x4, x8; struct VTE *vt; char pad[0x13D0 - 0x10]; int x13D0; };
struct S { void *p0; char pad[0xC]; struct O *po; char pad1[0x1C]; qword q30; char pad2[0xB0]; qword qF0; char pad3[0x2C]; struct O *p12C; };
extern struct O *D_002DD5BC;
void SetBentleyCarried__FP7BENTLEYi(struct O *po, int n);
void ReparentBooty__FP3ALOii(struct O *po, int a, int b);
void SetAloCnstrLin__FP3ALOi(struct O *po, int a);
void SetAloCnstrAng__FP3ALOi(struct O *po, int a);
qword ConvertVec__FP2LOT0G9VU_VECTOR(void *p, int a, qword q);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *po, int n);
void func_002205A8(struct S *p)
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
    p->po->vt[35].pfn((char *)p->po + p->po->vt[35].d, p->qF0);
    {
        struct VTE *pve;
        po = p->po;
        pve = &po->vt[36];
        po = (struct O *)((char *)po + pve->d);
        pve->pfn(po, ConvertVec__FP2LOT0G9VU_VECTOR(p->p0, 0, p->q30));
    }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p->po, 100))
        p->po->vt[76].pfn((char *)p->po + p->po->vt[76].d, 1);
tail:
    if (p->p12C)
        p->p12C->vt[9].pfn((char *)p->p12C + p->p12C->vt[9].d);
}
