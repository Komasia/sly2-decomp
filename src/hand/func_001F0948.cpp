struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x24 - 0x10]; void *p24; char pad3[0x3C - 0x28]; int n3C; };
extern "C" int FSmaRetracted(P *) asm("FSmaRetracted__FP3SMA");
extern "C" int func_001F0438(void *, int);
extern "C" void FinishSmaTransition(P *) asm("FinishSmaTransition__FP3SMA");
extern "C" void ChooseSmaTransition(P *, int) asm("ChooseSmaTransition__FP3SMAi");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (SnapSmaGoal)
extern "C" void SnapSmaGoal__FP3SMA3OID(P *p, int n)
{
    if (!FSmaRetracted(p)) {
        Lock l(p);
        p->n3C = func_001F0438(p->p24, n);
        FinishSmaTransition(p);
        ChooseSmaTransition(p, 1);
    }
}
