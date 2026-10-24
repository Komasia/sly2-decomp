/* laneG13v1 (Claude agent, 2026-10-24): laneG12v1 (21) -> 12. (1) the entry "+r"(p) asm is gone; instead a commented empty "+r"(pm) on the matrix pointer makes the matrix stores alias p->count (loop 1 exact, entry qmtc2 back in the beqz slot). (2) ONE pointer pm for both the matrix and rhs loops (target reuses a3; gives the bnel). (3) int weights[8] indexed as weights[i]: the load is then an in-struct MEM, so loop.c load_mems keeps the VU_FLOAT temp (0xD0) in a register and stores it once after loop 3 like the target. Left: loop 2 addiu a0/mtc1 order (+hazard nop), loop 3 count v0 + copy (target lw v1 directly), a0/v0 roles, epilogue qmfc2 order. */
/* laneG12v1 (Claude agent, 2026-10-24): laneG9v1 (34) -> 21. (1) commented empty asm with allocation-only "+r"(p) at entry: p's alias base becomes unknown, so the count reloads depend on the matrix/rhs stores (target: sw/swc1 before lw count; loop 1 now exact). (2) &p->planes[i] through an inline Addr() helper gives the (i*16+p)+16 address form, so the outer loop no longer hoists p+0x10 and loop 2 uses one giv. (3) a commented empty "=j"/"0" asm copy of v inside loop 2 (loop.c hoists it = the target vmove). (4) v is the parameter itself (a separate `qword v = raw` made cse use raw for the copy, adding a vmove). Left: entry qmtc2 not in the beqz slot, loop-2 rhs pointer a1 (target a3) and bnel, loop-3 count/pointer regs and the VU_FLOAT temp sqc2 (target once after the loop). */
/* laneG9v1 (Claude agent, 2026-10-24): laneG3v1 + loop 2 as plain `rhs = plane.w + GXOfQw(DotQ(v, plane))` (Lilly mtc1-from-qword helper; gcc emits the qmfc2): aligned 38 -> 34. Left: loop 2 lacks the target vmove copy of v and uses a +0x1C giv; loop 3 VU_FLOAT temp sqc2 is inside the loop (target: once after it); outer loop hoists p+0x10. Lilly-style QwDot without "memory" clobber = 55 (count loads hoisted, loops reversed). */
/* laneG3v1 (Claude agent): G2v1 with `qword v = raw;` as plain C (gcc puts the qmtc2 in the beqz delay slot like the target): 40 -> 38. Goto-built outer loop (41) / goto-into-body (38) / inner goto entry (62) no gain.
   lane G2 (Claude agent, 2026-10-24): clean rewrite (no pins, no lw/sw/lqc2 asms), aligned 40. Fused 4-insn Dot asm with plain "=j" outputs (no &) + "memory" clobber (count reloads), separate qmfc2 asm for the int bits, inner/RHS loops test p->count while the outer loop updates n = p->count. Left: outer loop hoists p+0x10 (target recomputes (i<<4)+p+0x10 each pass), loop1 lw count scheduled above qmfc2/sw, loop2 missing the target's vmove copy of v and uses a +0x1C giv, loop3 temp sqc2 is inside the loop (target after it). */
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
static inline qword *Addr(qword *q) { return q; }
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
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline qword Load(qword raw)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(raw));
    return q;
}
extern "C" qword func_00185A80(void *unused, P *p, qword v)
{
    int matrix[36];
    float rhs[8];
    int weights[8];
    int i, j, n;
    int *pm;
    n = p->count;
    if (n != 0) {
        pm = matrix;
        __asm__("" : "+r"(pm));
        for (i = 0; i < n; i++) {
            for (j = 0; j < p->count; j++)
                *pm++ = Bits(DotQ(*Addr(&p->planes[i]), p->planes[j]));
            n = p->count;
        }
        pm = (int *)rhs;
        for (i = 0; i < p->count; i++) {
            qword *pl = Addr(&p->planes[i]);
            qword point;
            __asm__("" : "=j"(point) : "0"(v)); /* empty: a VF copy of v (loop.c hoists it: the target's vmove) */
            *(float *)pm++ = ((float *)pl)[3] + GXOfQw(DotQ(point, *pl));
        }
        func_0011AD30(p->count, (float *)matrix, rhs, (float *)weights, D_002A568C);
        n = p->count;
        for (i = 0; i < n; i++)
            v = AddScaled(v, p->planes[i], VU_FLOAT(weights[i]));
    }
    return v;
}
