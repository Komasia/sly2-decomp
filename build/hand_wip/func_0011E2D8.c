typedef int qword __attribute__((mode(TI)));
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=j"(d) : "j"(v));
    return d;
}
static inline qword Normalize(qword v)
{
    qword d, l, r;
    d = Dot(v);
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static __inline__ float FloatQ(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
void func_0011E2D8(qword a, qword b, qword c, qword *pm)
{
    qword x = Cross(b, a);
    qword y;
    if (FloatQ(Dot(x)) < 1.0e-4f)
        x = Cross(c, a);
    y = Cross(a, x);
    pm[0] = Normalize(x);
    pm[1] = Normalize(y);
}
