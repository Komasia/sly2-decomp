struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; int n30; };
extern "C" void func_001F0FA0(P *);
extern "C" void func_001F0D88(P *, int);
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
extern "C" void func_001F1078(P *p, int k, int n)
{
    if (k == 2 && n == p->n30) {
        Lock l(p);
        func_001F0FA0(p);
        func_001F0D88(p, 0);
    }
}
