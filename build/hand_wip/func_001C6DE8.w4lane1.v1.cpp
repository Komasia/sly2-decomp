// w4lane1 v1: aligned 3 (same two diffs as w2lane8.v1), written in the style of the matched sibling func_001C6FD8
// (RAII FRAME with out-of-line ctor/dtor, plain returns, VV/VU_FLOAT AddScaled). No pins, no explicit dtor calls.
// Left: (1) `sw a2,0x84` must precede `sd ra`/`swc1 f20` (sched2 tie, needs one more dependent); (2) the bnez slot holds
// `lq a2,0xA0` in the target, which looks like the a2 argument was loaded in block 0 (see build/lane_notes/w4lane1.md).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct HIT { U a; U b; U normal; U otherNormal; float t; float u; char pad48[0x18]; };
struct FRAME { int n; FRAME(); ~FRAME(); };
struct O;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f)); } };
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
extern "C" {
int func_001C5570(void *, O *);
void func_0020FAA0(void *, qword, qword, int (*)(void *, O *), void *, int *, O ***);
O *PsoHitTestLineObjects(int, qword, qword, int, O **, HIT *) __asm__("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
extern char D_003DD490[];
extern qword D_002A2DC0;
}
static inline qword AddScaled(VV base, VU_FLOAT g, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base.q), "j"(v), "j"(g.q));
    return r;
}
extern "C" int func_001C6DE8(float lo, float hi, float threshold, qword point, int count0, O **objects0, qword *out)
{
    HIT hit; O **objects = objects0; int count = count0;
    FRAME frame;
    qword upper = AddScaled(point, VU_FLOAT(hi), D_002A2DC0);
    qword lower = AddScaled(point, VU_FLOAT(lo), D_002A2DC0);
    if (!objects) func_0020FAA0(D_003DD490, point, upper, func_001C5570, 0, &count, &objects);
    if (hi > 0) {
        if (PsoHitTestLineObjects(0, point, upper, count, objects, &hit) && hit.t == 0) {
            if (hit.u == 1 || hit.otherNormal.f[2] < threshold) return 0;
            *out = hit.b.q;
            return 1;
        }
    }
    if (lo < 0) {
        if (PsoHitTestLineObjects(0, point, lower, count, objects, &hit)) {
            if (hit.t == 0 || hit.normal.f[2] < threshold) return 0;
            *out = hit.a.q;
            return 1;
        }
        return 0;
    }
    *out = point;
    return 1;
}
