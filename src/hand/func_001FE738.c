struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[3]; };
struct X { char pad[0xC]; struct VT *pvt; };
struct A { int a, b; };
struct E { char pad[0x54]; int c; struct A *ae; };
struct Y { char pad[0x60]; struct E *pe; };
struct Ref { struct Y *px; };
struct P { char pad[0x200]; struct Ref r; char pad2[0x22C - 0x204]; struct X *ap[6]; int n244; int n248; float g24C; };
void FireDialogTarget__FP8SOUNDMGRPv(struct P *, struct A *);
void SetSmaGoal__FP3SMA3OID(void *, int);
void Stop__4CSndf(struct Y *, float);
void func_00259B48(struct Ref *, void *);
void s1_memset(void *, int, int) asm("memset");
static inline void Stop(struct Ref *pr)
{
    if (pr && pr->px) {
        Stop__4CSndf(pr->px, 0.0f);
        func_00259B48(pr, 0);
    }
}
// name: SafeHouse port (StopDialog)
void StopDialog__FP8SOUNDMGR(struct P *p)
{
    int i;
    struct E *pe;
    if (!p->r.px) return;
    pe = p->r.px->pe;
    while (p->n244 < pe->c) {
        FireDialogTarget__FP8SOUNDMGRPv(p, &pe->ae[p->n244]);
        p->n244++;
    }
    if (p->ap[5]) SetSmaGoal__FP3SMA3OID(p->ap[5], 0x611);
    Stop(&p->r);
    p->n244 = 0;
    p->n248 = 0;
    p->g24C = 0.0f;
    for (i = 0; i < 6; i++) {
        struct X *px = p->ap[i];
        if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d);
    }
    s1_memset(p->ap, 0, 0x18);
}
