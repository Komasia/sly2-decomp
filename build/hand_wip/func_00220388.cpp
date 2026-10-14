// Complete vector-state update WIP, all scalar and vector registers unbound.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } VU;
struct G { char pad[0x10]; qword v; };
extern struct G D_002DDFA0;
extern float D_002C4108;
union F32 {float f;int bits;};extern F32 D_002C410C;
extern qword D_002A2DD0;
struct Q { char pad[0x10]; qword v; qword w; };
struct S { int x0; int k; char pad[0xD8]; qword vE0; };
static inline qword ScalarHome(VU *home,float f){qword value;__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(f));home->q=value;return home->q;}
static inline qword WordHome(VU *home,int bits){qword value;__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(bits));home->q=value;return home->q;}
extern "C" void func_00220388(struct S *p, struct Q *q)
{
    G *movement=&D_002DDFA0;
    float c = D_002C4108;
    VU u;
    qword s,v;
    s=ScalarHome(&u,c);
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=&j"(v) : "j"(q->v), "j"(movement->v), "j"(s));
    q->v = v;
    if(p->k<7) if(p->k>=4) {
        qword *pw = &q->w;
        qword d,one,n,m1,nc,l,sc;
        VU w;
        float g;
        m1=ScalarHome(&w,-1.0f);
        nc=ScalarHome(&w,-c);
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x" : "=j"(d) : "j"(p->vE0), "j"(v), "j"(m1), "j"(movement->v), "j"(nc));
        u.q = d;
        u.n[2] = 0;
        sc=WordHome(&w,D_002C410C.bits);
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(u.q));
        float tolerance=1.0e-4f;
        __asm__ __volatile__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(l));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        if (g < tolerance) {
            n = D_002A2DD0;
        } else {
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(n) : "j"(l), "j"(u.q));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(n) : "j"(n), "j"(sc));
        }
        *pw = n;
    }
}
