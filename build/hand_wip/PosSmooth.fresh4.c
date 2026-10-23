typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DD0;
struct SMP;
float func_0011D018(float g, float gGoal, float dt, struct SMP *psmp, float *pdv);
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
qword PosSmooth(qword pos, qword posGoal, float dt, struct SMP *psmp, qword *pvVel)
{
    U s;
    U dv;
    U p, dp;
    float len;
    qword d;
    p.q = pos;
    { qword t = Sub(posGoal, pos); __asm__("sqc2 %1, %0" : "=m"(dp.q) : "j"(t)); }
    d = dp.q;
    len = F(Len(d));
    if (len > 1.0e-4f) {
        float g = func_0011D018(0.0f, len, dt, psmp, &dv.f);
        qword r, sc;
        if (pvVel) {
            __asm__("qmtc2.ni %1, %0" : "=j"(sc) : "r"(dv.f / len));
            s.q = sc;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(d), "j"(sc));
            *pvVel = r;
        }
        __asm__("qmtc2.ni %1, %0" : "=j"(sc) : "r"(g / len));
        s.q = sc;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p.q), "j"(dp.q), "j"(sc));
        return r;
    }
    if (pvVel)
        *pvVel = D_002A2DD0;
    return posGoal;
}
