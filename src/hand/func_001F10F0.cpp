struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct A { char pad[0x74]; float g74; };
struct Q { char pad[0x14]; A *pa; int pad2; float g1C; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x30 - 0x10]; Q *pq; };
extern "C" int FSmaRetracted(P *) asm("FSmaRetracted__FP3SMA");
extern "C" void RetractAsega(Q *) asm("RetractAsega__FP5ASEGA");
extern "C" void SetAsegaTime(Q *, int, float, float) asm("SetAsegaTime__FP5ASEGAiff");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
// name: SafeHouse port (AdvanceSma)
extern "C" void AdvanceSma__FP3SMAf(P *p, float t)
{
    if (!FSmaRetracted(p)) {
        Lock l(p);
        Q *q;
        while ((q = p->pq) != 0) {
            float d = q->pa->g74 - q->g1C;
            if (t < d) {
                SetAsegaTime(q, 1, t, 1.0f);
                break;
            }
            t -= d;
            RetractAsega(q);
        }
    }
}
