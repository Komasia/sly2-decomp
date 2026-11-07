typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short p; void *pfn; };
struct VT { struct VTE a[34]; };
struct O { char pad[0x94]; int n94; short k; char pad2[0xA0 - 0x9A]; int nA0; char pad3[0xB0 - 0xA4]; union { qword q; int a[4]; } v; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x58 - 0x10]; struct O *po; };
int FXfmMoving(int);
void SetXfMode__FP3ALOP2XFi(struct P *, struct O *, int);
qword VecConvertXfs__FP2XFT0G9VU_VECTOR(int, int, qword);
void HoldXfMode(struct P *, struct O *);
void MarkAloDirty__FP3ALO(struct P *);
void WakeAlo__FP3ALO(struct P *);
void SetAloIced__FP3ALOl(struct P *, int);
// name: SafeHouse port (SetAloVelocityToLoad)
void SetAloVelocityToLoad__FP3ALOG9VU_VECTOR(struct P *p, qword q)
{
    struct O *po = p->po;
    qword cur, d;
    if (!po || po->n94 != 1) return;
    if (!FXfmMoving(po->k)) SetXfMode__FP3ALOP2XFi(p, po, 1);
    { float *pv = (float *)&po->v; pv[2] = 0.0f; pv[1] = 0.0f; pv[0] = 0.0f; }
    cur = ((qword (*)(void *))p->pvt->a[33].pfn)((char *)p + p->pvt->a[33].d);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(q), "j"(cur));
    po->v.q = VecConvertXfs__FP2XFT0G9VU_VECTOR(0, po->nA0, d);
    HoldXfMode(p, po);
    MarkAloDirty__FP3ALO(p);
    WakeAlo__FP3ALO(p);
    SetAloIced__FP3ALOl(p, 0);
}
