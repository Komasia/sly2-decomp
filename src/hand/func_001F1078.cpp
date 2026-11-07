struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; int n30; };
extern "C" void EndSmaTransition(P *) asm("EndSmaTransition__FP3SMA");
extern "C" void ChooseSmaTransition(P *, int) asm("ChooseSmaTransition__FP3SMAi");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (SMA::OnAsegaMsg)
extern "C" void OnAsegaMsg__3SMAP5ASEGAi(P *p, int k, int n)
{
    if (k == 2 && n == p->n30) {
        Lock l(p);
        EndSmaTransition(p);
        ChooseSmaTransition(p, 0);
    }
}
