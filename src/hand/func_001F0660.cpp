struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct F { int pad[3]; int fl; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x24 - 0x10]; void *p24; char pad3[0x30 - 0x28]; void *p30; char pad4[0x3C - 0x34]; int n3C; F *pf; };
extern "C" int FSmaRetracted(P *) asm("FSmaRetracted__FP3SMA");
extern "C" int func_001F0438(void *, int);
extern "C" void RetractAsega(void *) asm("RetractAsega__FP5ASEGA");
extern "C" void ChooseSmaTransition(P *, int) asm("ChooseSmaTransition__FP3SMAi");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (SetSmaGoal)
extern "C" void SetSmaGoal__FP3SMA3OID(P *p, int n)
{
    if (FSmaRetracted(p)) return;
    n = n == -1 ? -1 : func_001F0438(p->p24, n);
    if (n != p->n3C) {
        Lock l(p);
        p->n3C = n;
        if (p->p30) {
            if (p->pf->fl & 2) RetractAsega(p->p30);
        } else ChooseSmaTransition(p, 0);
    }
}
