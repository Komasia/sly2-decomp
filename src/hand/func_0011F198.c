typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
static inline float Len(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %1, %2\n\tvaddw.x $vf2, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf2, %0z" : "=j"(d) : "j"(v), "j"(v) : "vf2");
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %1, %2\n\tvaddw.x $vf2, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf2, %0z" : "=j"(d) : "j"(a), "j"(b) : "vf2");
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline qword QF(float g) { U u; __asm__("mfc1 %0, %1" : "=r"(u.q) : "f"(g)); return u.q; }
qword func_0011F198(qword a, qword b)
{
    float g, lb;
    g = Len(a);
    if (g < 1.0e-4f) {
        g = 0.0f;
    } else {
        lb = Len(b);
        if (lb < 1.0e-4f)
            goto zero;
        { register float p __asm__("$f1") = g * lb; g = Dot(a, b) / p; }
    }
    return QF(g);
zero:
    return QF(0.0f);
}
