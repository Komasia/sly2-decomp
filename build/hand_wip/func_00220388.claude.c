/* v-claude (Claude agent, 2026-10-17): aligned 22->21 vs func_00220388.c. GPR-pinned fallback (register qword fb asm("v0") = D_002A2DD0; n asm("vf1")) gives the lq+qmtc2 default path. Remaining: target schedules eps const before vsqrt and lq fallback before c.lt.s (making vsqrt non-volatile is worse: 18 -> scheduling breaks earlier), and keeps the dead w.q=nc store (sqc2 vf4,0x10(sp)). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } VU;
struct G { char pad[0x10]; qword v; };
extern struct G D_002DDFA0;
extern float D_002C4108, D_002C410C;
extern qword D_002A2DD0;
struct Q { char pad[0x10]; qword v; qword w; };
struct S { int x0; int k; char pad[0xD8]; qword vE0; };
void func_00220388(struct S *p, struct Q *q)
{
    float c = D_002C4108;
    VU u;
    qword s; register qword v __asm__("vf5");
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(c));
    u.q = s;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=&j"(v) : "j"(q->v), "j"(D_002DDFA0.v), "j"(s));
    q->v = v;
    if(p->k<7) if(p->k>=4) {
        qword *pw = &q->w;
        qword d,one; register qword n __asm__("vf1"); register qword fb __asm__("v0"); register qword m1 __asm__("vf3"),nc __asm__("vf4"),l __asm__("vf1"),sc __asm__("vf6");
        VU w;
        float g;
        __asm__("qmtc2.ni %1, %0" : "=j"(m1) : "r"(-1.0f));
        __asm__("qmtc2.ni %1, %0" : "=j"(nc) : "r"(-c));
        w.q = m1;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x" : "=j"(d) : "j"(p->vE0), "j"(v), "j"(m1), "j"(D_002DDFA0.v), "j"(nc));
        u.q = d;
        u.n[2] = 0;
        __asm__("qmtc2.ni %1, %0" : "=j"(sc) : "r"(*(int *)&D_002C410C));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(u.q));
        __asm__ __volatile__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        fb = D_002A2DD0;
        w.q = nc;
        w.q = sc;
        if (g < 1.0e-4f) {
            n = fb;
        } else {
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(n) : "j"(l), "j"(u.q));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(n) : "j"(n), "j"(sc));
        }
        *pw = n;
    }
}
