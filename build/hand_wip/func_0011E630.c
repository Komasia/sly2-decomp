/* wip (Claude agent): triangle barycentric + normal. 39 diffs: entry VF allocation of a/b/c/pos, u/v qmfc2/div scheduling vs 3rd dot, final normalize join (target: one vmove vf5<-vf1 at join, lq default in bc1f delay). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DC0;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword DotQE(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float DotS(qword a, qword b)
{
    qword d = DotQ(a, b);
    int n;
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    return *(float *)&n;
}
static inline float Dot(qword a, qword b)
{
    qword d = DotQ(a, b);
    int n;
    float g;
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(d));
    return g;
}
void func_0011E630(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal)
{
    qword ca = Sub(c, a);
    qword ba = Sub(b, a);
    qword pc = Sub(pos, c);
    qword n = Cross(ba, pc);
    float lenSq = Dot(n, n);
    if (lenSq < 1e-4f) {
        puv[0] = puv[1] = 0.0f;
        n = ca;
    } else {
        qword c1 = Cross(ca, pc);
        qword c2 = Cross(ca, ba);
        float u = DotS(c1, n) / lenSq;
        float v = DotS(c2, n) / lenSq;
        puv[0] = u;
        puv[1] = v;
        if (Dot(ca, n) < 0.0f) {
            U s;
            float m = -1.0f;
            __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(m));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(n) : "j"(n), "j"(s.q));
        }
    }
    {
        register qword l __asm__("vf1");
        int gl;
        register qword rn __asm__("vf1");
        qword *pdef;
        {
            register qword one __asm__("vf2");
            __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(l), "=j"(one) : "j"(n));
        }
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
        __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
        pdef = &D_002A2DC0;
        __asm__("" : "+r"(pdef));
        if (*(float *)&gl < 1e-4f) {
            __asm__("qmtc2.ni %1, %0" : "=j"(rn) : "r"(*pdef));
        } else {
            __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(rn) : "j"(n), "j"(l));
        }
        n = rn;
    }
    {
        int nd;
        __asm__("qmfc2.ni %0, %1" : "=r"(nd) : "j"(DotQE(n, ca)));
        *(int *)pdist = nd;
    }
    *pnormal = n;
}
