/* fresh7 (Claude agent, lane A24, 2026-10-23): aligned 23 (fresh6 27). From fresh6: the two copies are explicit vmove asms (right block-0 order), and CrossT writes a NEW c2 tied "0"(ca2), so ca2 is local to block 0 (vf2) and n2 gets vf6 as in the target. Left: qmtc2 a1/ca vsub swap; c1 gets vf3 (ba dies at c1; target vf8, so n is vf8 not vf9), which also changes the u/v dot temps and their schedule. */
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
static inline float Dot(qword a, qword b)
{
    int n;
    float g;
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(DotQ(a, b)) : "memory");
    return g;
}
static inline float DotS(qword a, qword b)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(DotQ(a, b)));
    return g;
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
    __asm__("vmove.xyzw %0, %1" : "=j"(n2) : "j"(n) : "memory");
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
        float u = DotS(c2, n2) / lenSq;
        float v = DotS(c1, n2) / lenSq;
        puv[0] = u;
        puv[1] = v;
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
