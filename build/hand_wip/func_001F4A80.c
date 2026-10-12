typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct VTE { short d; short pad; void (*pfn)(); };
struct A { char pad[0x70]; qword pos; };
struct P { char pad[0xC]; struct VTE *pvt; char pad2[0xE8 - 0x10]; void *pe; };
void func_001A6BC8(struct P *p, struct A *pa);
M4 func_0022D148(struct A *pa, int n);
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__ __volatile__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
void func_001F4A80(struct P *p, struct A *pa)
{
    M4 m;
    qword r, q;
    func_001A6BC8(p, pa);
    if (!p->pe) return;
    { M4 t = func_0022D148(pa, 0); m = t; }
    q = Make(((float *)&m)[6], ((float *)&m)[8], ((float *)&m)[1]);
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(pa->pos));
    ((void (*)(void *, qword))p->pvt[35].pfn)((char *)p + p->pvt[35].d, r);
    {
        qword v[1];
        v[0] = q;
        ((void (*)(void *, qword))p->pvt[36].pfn)((char *)p + p->pvt[36].d, v[0]);
    }
}
