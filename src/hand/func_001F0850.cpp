struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; void *p30; char pad3[0x44 - 0x34]; float g; };
extern "C" int func_001F0638(P *);
extern "C" void func_00131A00(void *, float);
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
extern "C" void func_001F0850(P *p, float g)
{
    if (!func_001F0638(p)) {
        Lock l(p);
        p->g = g;
        if (p->p30) func_00131A00(p->p30, g);
    }
}
