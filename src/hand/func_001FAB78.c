typedef int qword __attribute__((mode(TI)));
struct O { char pad[0xA0]; int nA0; char pad3[0xF0 - 0xA4]; qword pos; };
struct P { char pad[0x58]; struct O *po58; struct O *po5C; };
qword DvAloImpulse__FP3ALOG9VU_VECTOR(struct P *, qword);
qword func_001FAA48(struct P *, qword, qword);
qword func_0022FCC8(int, int, qword);
static inline void Add(struct O *po, qword d)
{
    qword a = po->pos;
    qword r = func_0022FCC8(0, po->nA0, d);
    qword s;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(a), "j"(r));
    po->pos = s;
}
// name: SafeHouse port (ForceAt)
void ForceAt__FP3ALOG9VU_VECTORT1(struct P *p, qword a, qword b)
{
    qword x = DvAloImpulse__FP3ALOG9VU_VECTOR(p, b);
    qword y = func_001FAA48(p, a, b);
    Add(p->po58, x);
    Add(p->po5C, y);
}
