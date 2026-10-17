// v4 (Claude agent): ToF as one qmfc2/mtc1 asm with temp pinned to v0, division inline -> 2 diffs: target keeps the dead sqc2 of s before beqz $a3 and fills the slot with the ppos qmfc2. volatile U s keeps sqc2 before but leaves a nop slot.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline qword DotV(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float ToF(qword d)
{
    float g;
    register int r __asm__("v0");
    __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(r), "=f"(g) : "j"(d));
    return g;
}
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo) g = lo;
    else if (g > hi) g = hi;
    return g;
}
void func_0011EE08(qword pos, qword p0, qword p1, qword *ppos, float *pt, float *pdist)
{
    qword d = Sub(p1, p0);
    qword e0 = Sub(pos, p0);
    qword vd = DotV(d, d);
    qword vn = DotV(e0, d);
    float t = GClamp(ToF(vn) / ToF(vd), 0.0f, 1.0f);
    if (pt)
        *pt = t;
    if (ppos || pdist) {
        U s;
        qword c, q;
        __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(t));
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(p0), "j"(d), "j"(s.q));
        if (ppos) {
            __asm__("qmfc2.ni %0, %1" : "=r"(q) : "j"(c));
            *ppos = q;
        }
        if (pdist) {
            qword e, one, l;
            int g;
            e = Sub(pos, c);
            __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(e), "=j"(one) : "0"(e));
            __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(e));
            __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
            *(int *)pdist = g;
        }
    }
}
