/* v4 (Claude agent, 2026-10-23): aligned 5. From v2: SubR for ca with an allocation-only "r"(a) operand (entry VF regs a vf1/c vf2/b vf3), a commented empty volatile asm after ca (pos reuses vf1), eps hoisted into a local before ca. Left: qmtc2 a1 after ca; third dot scheduled before the divs (a barrier there fixes it but moves mtc1 zero late). */
/* v2 (Claude agent, aligned 11, was 25): gcc-emitted qmfc2 for dots ("=r" float), default via GPR qword def -> t pinned vf1 (lq in bc1f slot), final dot output pinned vf1 keeps n in vf5 (vmove at join). Left: entry VF allocation (target pos reuses a's vf1 = looks like a reload of $a3), dot3 scheduled before the divs. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DC0;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword SubR(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b), "r"(b));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
void func_0011E630(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal)
{
    qword ca, ba, pc, n;
    float lenSq;
    float eps = 1e-4f;
    ca = SubR(c, a);
    __asm__ volatile(""); /* emulates toolchain order */
    ba = Sub(b, a);
    pc = Sub(pos, c);
    n = Cross(ba, pc);
    lenSq = Dot(n, n);
    if (lenSq < eps) {
        puv[0] = puv[1] = 0.0f;
        n = ca;
    } else {
        float u = Dot(Cross(ca, pc), n) / lenSq;
        float v = Dot(Cross(ca, ba), n) / lenSq;
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
        qword def = D_002A2DC0;
        register qword t __asm__("vf1");
        qword one;
        float l;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(t), "=&j"(one) : "j"(n));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t) : "j"(t));
        __asm__("qmfc2.ni %0, %1" : "=r"(l) : "j"(t));
        if (l < 1e-4f) {
            t = def;
        } else {
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(t) : "j"(t), "j"(n));
        }
        n = t;
    }
    {
        register qword d __asm__("vf1");
        qword one;
        int nd;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(n), "j"(ca));
        __asm__("qmfc2.ni %0, %1" : "=r"(nd) : "j"(d));
        *(int *)pdist = nd;
    }
    *pnormal = n;
}
