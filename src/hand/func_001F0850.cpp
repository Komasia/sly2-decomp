struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; void *p30; char pad3[0x44 - 0x34]; float g; };
extern "C" int FSmaRetracted(P *) asm("FSmaRetracted__FP3SMA");
extern "C" void SetAsegaSpeed(void *, float) asm("SetAsegaSpeed__FP5ASEGAf");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (SetSmaSpeed)
extern "C" void SetSmaSpeed__FP3SMAf(P *p, float g)
{
    if (!FSmaRetracted(p)) {
        Lock l(p);
        p->g = g;
        if (p->p30) SetAsegaSpeed(p->p30, g);
    }
}
