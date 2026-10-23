typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { qword q; float f[4]; } U;
extern qword D_002A2DA0;
qword func_0011E390(qword v);
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
M3 *func_0011B830(M3 *pm, qword x, qword y)
{
    qword l;
    U z;
    register qword xn __asm__("vf4");
    register qword fb __asm__("v0");
    l = Len(x);
    fb = D_002A2DA0;
    if (F(l) < 1.0e-4f)
        xn = fb;
    else
        xn = Div(x, l);
    z.q = Cross(y, xn);
    pm->r[1] = z.q;
    l = Len(z.q);
    pm->r[0] = xn;
    {
    float g = F(l);
    pm->r[1] = Div(z.q, l);
    if (g < 1.0e-4f)
        pm->r[1] = func_0011E390(xn);
    }
    pm->r[2] = Cross(pm->r[0], pm->r[1]);
    return pm;
}
