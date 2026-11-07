struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x24 - 0x10]; void *p24; char pad3[0x30 - 0x28]; void *p30; int n34; int n38; int n3C; };
extern "C" int func_001F0638(P *);
extern "C" int func_001F0438(void *, int);
extern "C" void RetractAsega(void *) asm("RetractAsega__FP5ASEGA");
extern "C" void NotifySmaState(P *, int, int) asm("NotifySmaState__FP3SMAii");
extern "C" void ChooseSmaTransition(P *, int) asm("ChooseSmaTransition__FP3SMAi");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (SetSmaState)
extern "C" void SetSmaState__FP3SMA3OID(P *p, int n)
{
    if (!func_001F0638(p)) {
        Lock l(p);
        int m = func_001F0438(p->p24, n);
        if (p->n34 == m && (p->n3C == m || p->n3C == -1)) return;
        {
            void *pv = p->p30;
            int old;
            if (pv) {
                p->p30 = 0;
                RetractAsega(pv);
            }
            old = p->n34;
            p->n38 = -1; p->n3C = m; p->n34 = m;
            NotifySmaState(p, old, m);
            ChooseSmaTransition(p, 0);
        }
    }
}
