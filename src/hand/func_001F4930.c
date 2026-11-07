typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x98]; short k; char pad2[0xA0 - 0x9A]; int nA0; char pad3[0xB0 - 0xA4]; qword q; };
struct P { char pad[0x5C]; struct O *po; };
struct Q { char pad[0x60]; int n60; };
int FXfmMoving(int);
void SetXfMode__FP3ALOP2XFi(void *, struct O *, int);
qword VecConvertXfs__FP2XFT0G9VU_VECTOR(int, int, qword);
void HoldXfMode(void *, struct O *);
void MarkAloDirty__FP3ALO(void *);
void WakeAlo__FP3ALO(void *);
void SetAloIced__FP3ALOl(void *, int);
// name: SafeHouse port (SetAloAngVelocity)
void SetAloAngVelocity__FP3ALOG9VU_VECTOR(struct P *p, qword v)
{
    struct O *po;
    if (!FXfmMoving(p->po->k)) SetXfMode__FP3ALOP2XFi(p, p->po, 1);
    po = p->po;
    po->q = VecConvertXfs__FP2XFT0G9VU_VECTOR(((struct Q *)p)->n60, po->nA0, v);
    HoldXfMode(p, p->po);
    MarkAloDirty__FP3ALO(p);
    WakeAlo__FP3ALO(p);
    SetAloIced__FP3ALOl(p, 0);
}
