class C {
public:
    virtual void V1();
    virtual void V2();
    virtual void V3(int a, int b, float g0, float g1);
};
struct O { char pad[0x1c]; float f1c; char pad2[0x40 - 0x20]; float f40; };
struct S { int pad[7]; C *pc; int f20; O *po; };
extern "C" void FWrapAsegaTime(O *, float *, float *) asm("FWrapAsegaTime__FP5ASEGAPfT1");
extern "C" void Query(S *, int, int) asm("Query__4CTRLP7VECTOR4T1f");
// name: SafeHouse port (CTRLASEG::Query)
extern "C" void Query__8CTRLASEGP7VECTOR4T1f(S *p, int a, int b, float g) {
    if (p->pc) {
        O *po = p->po;
        float t, dt;
        dt = po->f40;
        t = po->f1c + g * dt;
        FWrapAsegaTime(po, &t, &dt);
        p->pc->V3(a, b, t, dt);
    } else {
        Query(p, a, b);
    }
}
