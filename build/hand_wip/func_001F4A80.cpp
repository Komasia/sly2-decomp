typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {U r[4];M4(){} M4(const M4&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];} M4&operator=(const M4&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];r[3]=m.r[3];return *this;}};
struct VTE { short d; short pad; void (*pfn)(); };
struct A { char pad[0x70]; qword pos; };
struct P { char pad[0xC]; struct VTE *pvt; char pad2[0xE8 - 0x10]; void *pe; };
extern "C" void func_001A6BC8(struct P *p, struct A *pa);
extern "C" M4 *func_0022D148(M4 *,A *,A *);
static inline M4 BuildVelocity(A *owner) return result { func_0022D148(&result,owner,0); }
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__ __volatile__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
extern "C" void func_001F4A80(struct P *p, struct A *pa)
{
    M4 m;
    qword r, q;
    func_001A6BC8(p, pa);
    if (!p->pe) return;
    { M4 t = BuildVelocity(pa); m = t; }
    register VTE *vt __asm__("$2")=p->pvt;
    register int delta __asm__("$4")=vt[35].d;
    q = Make(((float *)&m)[6], ((float *)&m)[8], ((float *)&m)[1]);
    void (*setpos)(void *,qword)=(void (*)(void *,qword))vt[35].pfn;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w" : "=j"(r) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(pa->pos));
    setpos((char*)p+delta,r);
    {
        qword v[1];
        v[0] = q;
        ((void (*)(void *, qword))p->pvt[36].pfn)((char *)p + p->pvt[36].d, v[0]);
    }
}
