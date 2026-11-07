typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VE *vt; char pad2[0x18]; unsigned long f28; };
struct T { char pad[0x180]; struct O *po; };
struct S { char pad[0x13F0]; struct T *pt; };
extern qword D_002C09D0, D_002A2DD0;
void func_001B7D20(struct S *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *p, int n);
void func_00209FB8(struct O *p);
qword ConvertVec__FP2LOT0G9VU_VECTOR(struct S *p, int n, qword q);
void SetAloEntryMode__FP3ALOi(struct O *p, int n);
// name: SafeHouse port (PutDownMurrayCarry)
void PutDownMurrayCarry__FP6MURRAY(struct S *p)
{
    struct O *po;
    qword q;
    func_001B7D20(p);
    po = p->pt->po;
    p->pt = 0;
    if ((int)(po->f28 >> 60) & 1) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(po, 0x38)) func_00209FB8(po);
        q = ConvertVec__FP2LOT0G9VU_VECTOR(p, 0, D_002C09D0);
        ((void (*)(void *, qword))po->vt[35].pfn)((char *)po + po->vt[35].d, q);
        ((void (*)(void *, qword))po->vt[36].pfn)((char *)po + po->vt[36].d, D_002A2DD0);
        SetAloEntryMode__FP3ALOi(po, 3);
    }
}
