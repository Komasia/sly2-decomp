typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x90]; int n90; char pad2[4]; short k; };
struct E { char pad[0x80]; qword q; };
struct P { char pad[0x58]; struct O *po; char pad2[0xE8 - 0x5C]; struct E *pe; };
void SetXfMode__FP3ALOP2XFi(struct P *, struct O *, int);
void WakeAlo__FP3ALO(struct P *);
// name: SafeHouse port (SetAloGravity)
void SetAloGravity__FP3ALOG9VU_VECTOR(struct P *p, qword q)
{
    if (p->pe) {
        struct O *po = p->po;
        if (po->n90 == 0 && po->k != 2) SetXfMode__FP3ALOP2XFi(p, po, 1);
        p->pe->q = q;
        WakeAlo__FP3ALO(p);
    }
}
