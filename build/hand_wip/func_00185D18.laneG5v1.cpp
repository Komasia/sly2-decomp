/* laneG5v1 (Claude agent): laneG2v1 + results computed into locals and stored at the end (fixes VF numbering), plus an allocation-only "r"(pvel) operand on the last AddScaled2 (fixes s1/s2). aligned 18 (G2v1 33). Left: pre-call arg/sqc2 interleave; post-call TRIREF copy is scheduled before the closest/normal lqc2s. */
/* lane G2 (Claude agent, 2026-10-24): clean rewrite, no pins, aligned 33. By-value VU_FLOAT class temps give the target's reused 0x30 temp slot; union-wrapped closest/normal get slots 0x10/0x20 at declaration. Left: VF numbering (vel vf6/t vf5/acc vf3), s1/s2 roles of ppos/pvel, post-call schedule (target copies TRIREF before the offset mfc1). */
typedef int qword __attribute__((mode(TI)));
struct TRIREF { int index; float a, b; };
extern "C" {
void func_00185310(void *p, qword v, int n, TRIREF *ptr, qword *ppos, qword *pnormal);
extern float D_002BE918;
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword AddScaled2(qword a, qword b, VU_FLOAT sb, qword c, VU_FLOAT sc)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
        : "=j"(r) : "j"(a), "j"(b), "j"(sb.q), "j"(c), "j"(sc.q));
    return r;
}
/* Same as AddScaled2; the extra "r"(hint) operand is allocation-only (emits nothing). */
static inline qword AddScaled2H(qword a, qword b, VU_FLOAT sb, qword c, VU_FLOAT sc, void *hint)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
        : "=j"(r) : "j"(a), "j"(b), "j"(sb.q), "j"(c), "j"(sc.q), "r"(hint));
    return r;
}
extern "C" int func_00185D18(void *p, qword pos, qword vel, qword acc, TRIREF *ptr, qword *ppos, qword *pvel, float offset, float t)
{
    TRIREF tr;
    union { qword q; } closest, normal;
    func_00185310(p, AddScaled2(pos, vel, VU_FLOAT(t), acc, VU_FLOAT((t * 0.5f) * t)), 0, &tr, &closest.q, &normal.q);
    *ptr = tr;
    qword rp = AddScaled(closest.q, normal.q, VU_FLOAT(offset));
    qword rv = AddScaled2H(vel, acc, VU_FLOAT(t), normal.q, VU_FLOAT(D_002BE918), pvel);
    *ppos = rp;
    *pvel = rv;
    return 1;
}
