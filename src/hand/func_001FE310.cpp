struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[8]; };
struct X { char pad[0xC]; VT *pvt; char pad2[0x40 - 0x10]; int n40; char pad3[0x50 - 0x44]; unsigned short fl; unsigned short c52; };
struct S { int c; void *a[8]; };
struct P { char pad[0x204]; S s; };
struct Ref {
    X *px;
    ~Ref() { if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d); }
};
extern "C" void RefTakeMusic(Ref *, P *, int) asm("RefTakeMusic__FP8SOUNDMGRi");
extern "C" void Stop(X *, float) asm("Stop__4CSndf");
extern "C" void func_00259B48(Ref *, void *);
// name: SafeHouse port (PopMusic)
extern "C" void PopMusic__FP8SOUNDMGRi(P *p, int n)
{
    Ref r;
    RefTakeMusic(&r, p, n);
    if (r.px) {
        int f = 0;
        if (!r.px->n40) { f = r.px->c52 || (r.px->fl & 1); f ^= 1; }
        if (!f) {
            Stop(r.px, 0.0f);
            func_00259B48(&r, p->s.c > 0 ? *(p->s.a + p->s.c - 1) : 0);
            if (r.px) r.px->pvt->a[7].pfn((char *)r.px + r.px->pvt->a[7].d);
        }
    }
}
