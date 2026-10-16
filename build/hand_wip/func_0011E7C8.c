/* wip (Claude agent): closest point via func_0011E630 + clamp u,v + weighted sum + normalize. 44 diffs: scheduling of the mfc1/qmtc2 weight moves vs the lqc2 reloads of a..pos (target alternates v0/v1, does all scalar math first), plus the length-block VF regs. Weights-first asm operand order already applied. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DA0;
void func_0011E630(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal);
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (g > hi)
        return hi;
    return g;
}
static inline qword VF(float g)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(g));
    return q;
}
void func_0011E7C8(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal)
{
    float v;
    U t;
    qword w0, w1, w2, w3, n, l, one;
    int nl;
    float gl;
    func_0011E630(a, b, c, pos, puv, pdist, pnormal);
    puv[0] = GClamp(puv[0], 0.0f, 1.0f);
    v = GClamp(puv[1], 0.0f, 1.0f);
    w0 = VF(puv[0] - 1.0f);
    w1 = VF(-puv[0]);
    w2 = VF(1.0f - v);
    w3 = VF(v);
    __asm__("vmulax.xyzw $ACC, %5, %1x\n\tvmaddax.xyzw $ACC, %6, %2x\n\tvmaddax.xyzw $ACC, %7, %3x\n\tvmaddx.xyzw %0, %8, %4x"
            : "=j"(n) : "j"(w0), "j"(w1), "j"(w2), "j"(w3), "j"(a), "j"(b), "j"(c), "j"(pos));
    *(volatile qword *)&t.q = w0;
    *(volatile qword *)&t.q = w1;
    *(volatile qword *)&t.q = w2;
    *(volatile qword *)&t.q = w3;
    *pnormal = n;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(l), "=j"(one) : "j"(n));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
    puv[1] = v;
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(nl), "=f"(gl) : "j"(l));
    if (gl < 1e-4f) {
        *pnormal = D_002A2DA0;
    } else {
        qword r;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(n), "j"(l));
        *pnormal = r;
    }
    __asm__("qmfc2.ni %0, %1" : "=r"(nl) : "j"(l));
    *(int *)pdist = nl;
}
