/* v4 (Claude agent, 2026-10-23): aligned 6. Dead stack copy of z as an ARRAY (qword t[1]; t[0] = z;) before the second Div fixes the second half; fb v0 pin removed (xn vf4 pin kept). Left: first Len result vf2 / y vf1 (target swapped). */
/* v2 (Claude agent, 2026-10-17): aligned 17->15. Pinning the default axis to a GPR (register qword fb asm("v0") = D_002A2DA0, xn asm("vf4"), as in src/hand/func_00224698.cpp) reproduces the lq+qmtc2 fallback path. Remaining: first Len result in vf1 / y in vf2 (ours swapped; tying sqrt output "0"(d) makes it worse), and the second half (target: mtc1 before vdiv, normalized z in vf2, dead caller-save sqc2 vf1,0(sp) of z across the call -> 0x30 frame). */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
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
    qword l, z;
    register qword xn __asm__("vf4");
    qword fb;
    l = Len(x);
    fb = D_002A2DA0;
    if (F(l) < 1.0e-4f)
        xn = fb;
    else
        xn = Div(x, l);
    z = Cross(y, xn);
    pm->r[1] = z;
    l = Len(z);
    pm->r[0] = xn;
    { qword t[1]; t[0] = z; }
    pm->r[1] = Div(z, l);
    if (F(l) < 1.0e-4f)
        pm->r[1] = func_0011E390(xn);
    pm->r[2] = Cross(pm->r[0], pm->r[1]);
    return pm;
}
