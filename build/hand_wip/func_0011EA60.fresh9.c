/* fresh9 (Claude agent, lane A27, 2026-10-23): aligned 13 (fresh8: 23). (1) The puv-block dots use DotN, a DotQ WITHOUT the "memory" clobber, so sched1 can interleave them (c1 = vf8 role fixed, n = vf9); (2) an allocation-only "j"(ca) on the n2 vmove asm gives ca more refs, so global-alloc takes ca before c1 (ca vf7, c1 vf8 like the target). Left: qmtc2 a1 vs ca vsub order; puv u/v in f1/f0 (target f0/f1); g dot: its d is combined into the $2 pin (or gets $2 from local-alloc with an unpinned mtc1), so the output reload takes vf2 and one vf1 (target d vf1, one vf2). One pin, in F2. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b) : "memory");
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b) : "memory");
    return r;
}
static inline qword CrossT(qword a, qword b)
{
    __asm__("vopmula.xyz $ACC, %0, %1\n\tvopmsub.xyz %0, %1, %0" : "+j"(a) : "j"(b) : "memory");
    return a;
}
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b) : "memory");
    return d;
}
static inline qword DotN(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float Dot(qword a, qword b)
{
    int n;
    float g;
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(DotQ(a, b)) : "memory");
    return g;
}
static inline float F2(qword q)
{
    float g;
    register qword t __asm__("$2") = q;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(t));
    return g;
}
static inline float DotS(qword a, qword b)
{
    return F2(DotQ(a, b));
}
int func_0011EA60(qword a, qword b, qword c, qword d, float *puv, qword *pnormal)
{
    qword ca = Sub(c, a);
    qword ba = Sub(b, a);
    qword dc = Sub(d, c);
    qword n = Cross(ba, dc);
    qword ca2, n2, c1, lq, c2;
    float lenSq;
    float g, s;
    __asm__("vmove.xyzw %0, %1" : "=j"(ca2) : "j"(ca) : "memory");
    __asm__("vmove.xyzw %0, %1" : "=j"(n2) : "j"(n), "j"(ca) : "memory"); /* "j"(ca): allocation-only operand */
    c1 = Cross(ca2, ba);
    lq = DotQ(n2, n2);
    __asm__("vopmula.xyz $ACC, %0, %2\n\tvopmsub.xyz %0, %2, %0" : "=j"(c2) : "0"(ca2), "j"(dc) : "memory");
    {
        int k;
        __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(k), "=f"(lenSq) : "j"(lq) : "memory");
    }
    if (lenSq < 1e-6f)
        return 0;
    if (puv) {
        qword du = DotN(c2, n2);
        qword dv = DotN(c1, n2);
        puv[0] = F2(du) / lenSq;
        puv[1] = F2(dv) / lenSq;
    }
    g = DotS(ca, n2);
    s = 1.0f;
    if (g < 0.0f)
        s = -1.0f;
    if (pnormal) {
        float l;
        U t;
        qword r;
        __asm__("sqrt.s %0, %1" : "=&f"(l) : "f"(lenSq));
        __asm__("qmtc2.ni %1, %0" : "=j"(t.q) : "r"(s / l));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(n), "j"(t.q));
        *pnormal = r;
    }
    return 1;
}
