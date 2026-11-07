struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[18]; };
struct X { char pad[0xC]; struct VT *pvt; };
struct E { int fl; struct X *px; };
struct P { char pad[0x3F14]; int c; int pad2; int *pi; struct E *ae; };
void UpdateSwXps__FP2SW(struct P *);
void SolvePassSw__FP2SWi(struct P *, int);
void func_001F8DD8(struct P *p)
{
    int i;
    UpdateSwXps__FP2SW(p);
    p->pi = &i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if ((pe->fl & 0x24) == 4) pe->px->pvt->a[17].pfn((char *)pe->px + pe->px->pvt->a[17].d);
    }
    p->pi = 0;
    SolvePassSw__FP2SWi(p, 1);
    UpdateSwXps__FP2SW(p);
    SolvePassSw__FP2SWi(p, 6);
}
