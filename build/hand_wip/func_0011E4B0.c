/* wip (Claude agent): angle between vectors + optional normalized axis (perpendicular fallback func_0011E390,
   default D_002A2DA0), returns acosf(dot/(la*lb)). Structure right; diffs: la/lb qmfc2/mtc1 must be separate asms
   (eps load and sq s0 scheduled between), axis VU_FLOAT must be qmtc2'd from the qmfc2 GPR (no mfc1), and the final
   la*lb mul.s is hoisted into a beql delay slot in ours (evaluate the dot first). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DA0;
qword func_0011E390(qword v);
float func_002456F0(float g);
static inline float Len(qword a)
{
    qword d, one;
    int n;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(d));
    return g;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    int n;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(d));
    return g;
}
float func_0011E4B0(qword a, qword b, qword *paxis)
{
    float la = Len(a);
    float lb = Len(b);
    if (la < 1e-4f || lb < 1e-4f) {
        if (paxis)
            *paxis = D_002A2DA0;
        return 0.0f;
    }
    if (paxis) {
        qword axis;
        float l;
        __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(axis) : "j"(a), "j"(b));
        l = Len(axis);
        if (l > 1e-8f) {
            U s;
            __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(l));
            __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(axis) : "j"(axis), "j"(s.q));
        } else {
            axis = func_0011E390(a);
        }
        *paxis = axis;
    }
    return func_002456F0(Dot(a, b) / (la * lb));
}
