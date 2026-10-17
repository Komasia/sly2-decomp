// v2 (Claude agent): aligned 9 -> 8 using the func_0011EE08 ppos/sqc2 fix (volatile sqc2 asm + empty-asm reload qmfc2). Left: d/p0 VF numbers (vf6/vf5 swapped), vmove before e0 vsub, n qmfc2 right after first dot.
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
    __asm__("vmul.xyz %0, %0, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "0"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
void func_0011ED40(qword pos, qword p0, qword p1, qword *ppos, float *pt, float *pdist)
{
    qword d = Sub(p1, p0);
    float n = Dot(Sub(pos, p0), d);
    float t = n / Dot(d, d);
    if (pt)
        *pt = t;
    if (ppos || pdist) {
        qword s, buf;
        qword c, q;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(t));
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(p0), "j"(d), "j"(s));
        __asm__ __volatile__("sqc2 %1, %0" : "=m"(buf) : "j"(s));
        if (ppos) {
            __asm__("" : "=r"(q) : "0"(c));
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
