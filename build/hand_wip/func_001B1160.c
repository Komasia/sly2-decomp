typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VT { short d; short pad; void *pfn; };
struct P { char pad0[0xC]; struct VT *vt; char pad1[0x16C - 0x10]; void *p16C; void *p170; float g174; float g178;
    char pad2[0x1CC - 0x17C]; float g1CC; float g1D0; char pad3[0x220 - 0x1D4]; int x220; };
extern qword D_002A2DA0;
qword func_001A62E8(void *p);
void func_001E6ED8(void *p, qword pos, int a, int b, int c, float g, float *pg, int d);
float func_001E6660(void *p, float g);
float func_001E6610(void *p);
float func_001E6630(void *p);
void func_001E67B8(void *p, qword *pv, int n, float g);
void func_001B1328(struct P *p, int n);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    {
    qword r;
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(r) : "j"(l));
    return r;
    }
}
void func_001B1160(struct P *p)
{
    void *q;
    float g, t;
    VU upos;
    switch (p->x220) {
    case 1:
        q = p->p16C;
        g = p->g1CC;
        break;
    case 4:
        q = p->p170;
        g = p->g1D0;
        break;
    default:
        q = 0;
        break;
    }
    if (!q)
        return;
    upos.q = func_001A62E8(p);
    func_001E6ED8(q, upos.q, 0, 0, 0, p->g174, &p->g174, 0);
    t = func_001E6660(q, p->g174 + p->g178);
    if (t < func_001E6610(q) || func_001E6630(q) < t) {
        if (p->x220 == 1)
            func_001B1328(p, 2);
    } else {
        VU v, uc, ur, ub;
        qword d, c, l, n, k, b, r;
        float gl;
        func_001E67B8(q, &v.q, 0, t);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v.q), "j"(upos.q));
        k = D_002A2DA0;
        __asm__("vmove.xyzw %0, %1" : "=j"(c) : "j"(d));
        uc.q = c;
        l = VLen(c);
        __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
        if (gl < 1e-4f) {
            n = k;
        } else {
            __asm__ __volatile__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(n) : "j"(d), "j"(l));
        }
        __asm__("qmtc2.ni %1, %0" : "=j"(b) : "r"(g));
        ub.q = b;
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(n), "j"(b));
        ur.q = r;
        ((void (*)(void *, qword))p->vt[35].pfn)((char *)p + p->vt[35].d, r);
    }
}
