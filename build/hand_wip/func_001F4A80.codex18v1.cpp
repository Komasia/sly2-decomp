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
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
typedef void (*SETVECTOR)(void *,qword);
extern "C" void func_001F4A80(struct P *p, struct A *pa)
{
    M4 m;
    qword q;
    func_001A6BC8(p, pa);
    if (!p->pe) return;
    { M4 t = BuildVelocity(pa); m = t; }
    VTE *vt=p->pvt;
    int delta=vt[35].d;
    q = Make(m.r[1].f[2],m.r[2].f[0],m.r[0].f[1]);
    SETVECTOR setpos;
    {
        register qword r __asm__("vf6");
    __asm__ volatile("lw %1,%7\n\tvmulax.xyz $ACC, %2, %6x\n\tvmadday.xyz $ACC, %3, %6y\n\tvmaddaz.xyz $ACC, %4, %6z\n\tvmaddw.xyz %0, %5, $vf0w" : "=&j"(r), "=&r"(setpos) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(pa->pos), "m"(vt[35].pfn));
    U v; v.q = q;
    qword rr;__asm__("qmfc2.ni %0,%1":"=r"(rr):"j"(r));
    setpos((char*)p+delta,rr);
    }
    {
        ((void (*)(void *, qword))p->pvt[36].pfn)((char *)p + p->pvt[36].d, q);
    }
}
