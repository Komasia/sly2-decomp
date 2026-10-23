typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
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
static inline qword CrossT(qword a, qword b)
{
    __asm__("vopmula.xyz $ACC, %0, %1\n\tvopmsub.xyz %0, %1, %0" : "+j"(a) : "j"(b));
    return a;
}
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float Dot(qword a, qword b)
{
    int n;
    float g;
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(DotQ(a, b)));
    return g;
}
static inline float DotS(qword a, qword b)
{
    int n;
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(DotQ(a, b)));
    return *(float *)&n;
}
static inline int Uv(qword ca, qword n, qword ba, qword dc, float *puv, float *plenSq)
{
    qword c1 = Cross(ca, ba);
    float lenSq = Dot(n, n);
    ca = CrossT(ca, dc);
    *plenSq = lenSq;
    if (lenSq < 1e-6f)
        return 0;
    if (puv) {
        float u = DotS(ca, n) / lenSq;
        float v = DotS(c1, n) / lenSq;
        puv[0] = u;
        puv[1] = v;
    }
    return 1;
}
int func_0011EA60(qword a, qword b, qword c, qword d, float *puv, qword *pnormal)
{
    qword ca = Sub(c, a);
    qword ba = Sub(b, a);
    qword dc = Sub(d, c);
    qword n = Cross(ba, dc);
    float lenSq;
    float g, s;
    if (!Uv(ca, n, ba, dc, puv, &lenSq))
        return 0;
    g = Dot(ca, n);
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
