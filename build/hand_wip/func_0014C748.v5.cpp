// v5 (Claude agent, lane D14): still 41, but posCenter/pos1 stack homes now match (0x30/0x20): the loop Sub takes VU_VECTOR params (SubV), so posCenter is made addressable after pos1 and gets the later reload slot. Adding a "memory" clobber to Sub dir (SubM) gives the target op order (lqc2 pos1 + vsub dir after the 1st qmfc2) but 49 aligned due to VF numbering (target: d vf1, posCenter vf2, Dot r vf3/t vf4).
// v4 (Claude agent, lane D13): 50 -> 41. "memory" clobbers on both Dot asms (vmul chain and the qmfc2); this also fixes the posCenter/pos1 stack homes (0x30/0x20). Repeated allocation-only operands on Dot/Sub/VecCombo/VLen/vdiv: no gain (50-59). Left: Sub dir still hoisted above Dot(d,d) (target: lqc2 pos1 + vsub after the first qmfc2), float tail order. Tried on top: volatile qmfc2 (51), empty barrier before Sub dir (51), mtc1-from-qword Dot (43-47), Dot split into vmul + vadd asms (46-51).
// v3 (Claude agent, lane D11): 62 -> 50. Normalize as func_0015A808: split VLen (length-squared asm with "memory" + separate vsqrt asm), returns a struct BY VALUE, default D_002A2DA0 passed as a by-value qword param (lq a1 now in the target block). Left: posCenter/pos1 home slots swapped, pre-loop VU/float schedule, lq a1 lands before the Sub (target: after qmfc2), loop-head alignment nop.
// v2 (Claude agent, lane D9): 67 -> 62. Early `if (cMax <= 0) return 0;` and `if (1.0f < t0 && 1.0f < t1) return 0;` (target: params read from stack homes 0x30/0x20). Also try: all Dot/Sub asms volatile (target VU order Sub d, Dot dd, Sub dir, Dot, Dot) + Normalize `if (g<eps) r = vDefault; else vdiv` = 64 but the loop then matches except VF numbering; left: posCenter/pos1 home slots swapped (target posCenter 0x30), 1.0 test slots.
typedef int qword __attribute__((mode(TI)));
struct PLANE { qword q; };
struct LSG { qword apos[2]; PLANE aplane[2]; float at[2]; int c; };
extern "C" {
extern qword D_002A2DA0;
void func_00119390(PLANE *pplane, qword vecNormal, qword vecPos);
int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int cMax, LSG *plsg);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(t) : "j"(a), "j"(b) : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r) : "memory");
    return g;
}

static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %4x" : "=j"(r) : "j"(v1.q), "j"(v2.q), "j"(f1.q), "j"(f2.q));
    return r;
}

struct VV { qword q; };
static inline qword SubV(VU_VECTOR a, VU_VECTOR b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q)); return r; }
static inline qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=&j"(l) : "j"(c) : "memory");
    {
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(l));
    return r;
    }
}
static inline VV Normalize(qword d, qword k)
{
    VV dir;
    qword l = VLen(d);
    float gl;
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        dir.q = k;
    } else {
        qword dq;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dq) : "j"(d), "j"(l));
        dir.q = dq;
    }
    return dir;
}

int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int cMax, LSG *plsg)
{
    float at[2];
    int i;
    if (cMax <= 0)
        return 0;
    qword d = Sub(pos0, posCenter);
    float c = Dot(d, d) - sRadius * sRadius;
    qword dir = Sub(pos1, pos0);
    float b = Dot(dir, d);
    float a = Dot(dir, dir);
    float disc;
    b = b + b;
    disc = b * b - a * (c * 4.0f);
    if (disc < 0.0001f)
        return 0;
    disc = __builtin_sqrtf(disc);
    {
        float t0 = (-b - disc) / (a + a);
        float t1 = (-b + disc) / (a + a);
        at[0] = t0;
        at[1] = t1;
        if (t0 < 0.0f && t1 < 0.0f)
            return 0;
        if (1.0f < t0 && 1.0f < t1)
            return 0;
    }
    at[1] = (1.0f < at[1] ? 1.0f : at[1]);
    at[0] = (0.0f < at[0] ? at[0] : 0.0f);
    for (i = 0; i < 2; i++) {
        float t = at[i];
        qword pos;
        plsg->at[i] = t;
        pos = VecCombo(VU_FLOAT(t), pos1, VU_FLOAT(1.0f - t), pos0);
        plsg->apos[i] = pos;
        func_00119390(&plsg->aplane[i], Normalize(SubV(pos, posCenter), D_002A2DA0).q, pos);
    }
    plsg->c = 1;
    return 1;
}
