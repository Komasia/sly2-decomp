/* lane G2 (Claude agent, 2026-10-24): clean rewrite (no pins, no lw/sw/lqc2 asms), aligned 40. Fused 4-insn Dot asm with plain "=j" outputs (no &) + "memory" clobber (count reloads), separate qmfc2 asm for the int bits, inner/RHS loops test p->count while the outer loop updates n = p->count. Left: outer loop hoists p+0x10 (target recomputes (i<<4)+p+0x10 each pass), loop1 lw count scheduled above qmfc2/sw, loop2 missing the target's vmove copy of v and uses a +0x1C giv, loop3 temp sqc2 is inside the loop (target after it). */
typedef int qword __attribute__((mode(TI)));
struct PLANE { qword q; };
struct P { int count; int pad[3]; qword planes[6]; };
extern "C" {
extern float D_002A568C;
void func_0011AD30(int n, float *matrix, float *rhs, float *weights, float eps);
}
struct VU_FLOAT { qword q; VU_FLOAT(int bits) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(bits)); } };
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
        : "=j"(d), "=j"(one) : "j"(a), "j"(b) : "memory");
    return d;
}
static inline int Bits(qword d)
{
    int r;
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Load(qword raw)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(raw));
    return q;
}
extern "C" qword func_00185A80(void *unused, P *p, qword raw)
{
    int matrix[36];
    float rhs[8];
    float weights[8];
    int i, j, n;
    n = p->count;
    qword v = Load(raw);
    if (n != 0) {
        int *pm = matrix;
        for (i = 0; i < n; i++) {
            for (j = 0; j < p->count; j++)
                *pm++ = Bits(DotQ(p->planes[i], p->planes[j]));
            n = p->count;
        }
        float *pr = rhs;
        for (i = 0; i < p->count; i++) {
            union { int i; float f; } d;
            d.i = Bits(DotQ(v, p->planes[i]));
            *pr++ = ((float *)&p->planes[i])[3] + d.f;
        }
        func_0011AD30(p->count, (float *)matrix, rhs, weights, D_002A568C);
        n = p->count;
        for (i = 0; i < n; i++)
            v = AddScaled(v, p->planes[i], VU_FLOAT(((int *)weights)[i]));
    }
    return v;
}
