/* wip (Claude agent): angle between vectors + optional normalized axis (fallback func_0011E390, default D_002A2DA0), returns acosf(dot/(la*lb)). ~14 real diffs, all in the entry block: the prologue saves (sq s0 / swc1 f20 / sd ra) and the lb c.lt/vsqrt are scheduled differently. Everything after the first branch matches (split dot asm + empty volatile barrier for la*lb, qmtc2 of the axis length from the qmfc2 GPR, pinned VF/GPR/FPR register locals). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DA0;
qword func_0011E390(qword v);
float func_002456F0(float g);
static inline float Len(qword a)
{
    register qword d __asm__("vf2");
    register qword one __asm__("vf3");
    register int n __asm__("$2");
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(d));
    return g;
}
static inline float LenS(qword a)
{
    register qword d __asm__("vf1");
    register qword one __asm__("vf2");
    int n;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(n));
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
    float la = LenS(a);
    float lb = Len(b);
    if (la < 1e-4f || lb < 1e-4f) {
        if (paxis)
            *paxis = D_002A2DA0;
        return 0.0f;
    }
    if (paxis) {
        qword axis;
        register float l __asm__("$f1");
        int n;
        __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(axis) : "j"(a), "j"(b));
        {
            qword d, one;
            __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(axis));
            __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
            __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(l) : "j"(d));
        }
        if (l > 1e-8f) {
            U s;
            __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(n));
            __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(axis) : "j"(axis), "j"(s.q));
        } else {
            axis = func_0011E390(a);
        }
        *paxis = axis;
    }
    {
        qword dq, one;
        int n;
        float d, p;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(dq), "=j"(one) : "j"(a), "j"(b));
        __asm__ __volatile__("");
        p = la * lb;
        __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(d) : "j"(dq));
        return func_002456F0(d / p);
    }
}
