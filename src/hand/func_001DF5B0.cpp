// CollectLaserDraws__FP3ALO (w2lane4, wave 2): the laser's per-frame draw (vt slot 19; h3_laser.h).
// After the SO's own draw (RenderSoSelf) and a camera visibility test of the laser's bounding sphere
// (FInsideCmPlanes), each beam is queried for its two end points and its length (func_001DEF98). A beam longer than its
// visible length (cut at its nearest contact) is pulled back toward the first point, then the laser's line model, the
// stretched middle model and the two end-cap models (AppendLaserLine / AppendAloExtraDraws) are placed along the
// segment, in a basis built from the segment direction (BuildLookAtMatrix); a cap with a scale channel is sized by it.
// Matching notes (all found by reading the sched1/local-alloc/reload dumps):
//  * The radius temporary VU_FLOAT(const float *, int) is a volatile empty asm (word load into a 128-bit GPR value); it acts as the
//    scheduler barrier that keeps the camera/bound loads before the call arguments, which is what puts the camera address
//    straight into $a0 and the bound pointer in $v1.
//  * g_normalZ must NOT be const: a const global would be an unchanging load that sched2 moves above the spill store of `dir`.
//  * `dir` is a plain qword that lives across BuildLookAtMatrix, so it is spilled (store right after the vsub, reload for the
//    argument and for Length). Length lists its input twice (as in the other matched Length/Dot helpers), which decides the
//    reload register.
//  * BuildLookAtMatrix / func_0011C210 return M3 / M4 by value (hidden result pointer), assigned to locals.
//  * `matrix` is declared at link-loop scope and the facing branch writes rows 1/2 and the corner through a pointer
//    (pm), rows 0 and the w words directly: that is the mixed sp / s2 addressing of the original.
#include "vtbl.h"
#include "h3_laser.h"
union U { qword q; float f[4]; int bits[4]; };
struct M3 { U rows[3]; };
struct M4 { U rows[4]; };
struct ASEGA { char pad0[0x1C]; float t; char pad20[0x20]; float svt; };   // asega.h ASEGA: time, speed
struct EVAL { VTENT *vt; };   // a channel evaluator: slot 3 evaluates it at (t, svt)
struct CAP { void *palo; void *paseg; ASEGA *pasega; EVAL *pevalScale; };   // h3_laser.h LASERCAP
struct OXA { char pad0[0x20]; U posCenter; float sRadius; };   // bound-box attachment (SafeHouse port)
struct LASER {
    char pad0[0xEC]; OXA *poxa; char padF0[0xA0];   // the SO base
    void *paloLine, *paloStretch;   // field: SafeHouse port (laserrender.cpp +0x190 / +0x194)
    int cpair; LASERPAIR *apair; CAP acap[2];
};
struct CAMERA { char pad0[0x90]; U position; };
extern CAMERA g_cm;
extern qword g_normalZ;
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
    /* barrier: loads the float's word into a 128-bit GPR value without any instruction of its own */
    VU_FLOAT(const float *p, int) { __asm__ __volatile__("" : "=r"(q) : "0"(*(const int *)p)); }
};
extern "C" {
void RenderSoSelf(LASER *) asm("RenderSoSelf__FP2SOP2CMP2RO");
int FInsideCmPlanes(CAMERA *, qword, VU_FLOAT) asm("FInsideCmPlanes__FP2CMG9VU_VECTORT1");
void func_001DEF98(LASER *, LASERPAIR *, qword *, float *);
void AppendLaserLine(void *, qword, qword, float, float) asm("AppendLaserLine__FP5SCENEG9VU_VECTORT1ff");
M3 BuildLookAtMatrix(qword, qword) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
M4 func_0011C210(qword, const M3 *, const U *);
qword *func_00256D18(qword *, qword);
void AppendAloExtraDraws(void *, const M4 *, float, float) asm("AppendAloExtraDraws__FP5SCENEP3ALOff");
}
static inline qword Subtract(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Scale(qword a, VU_FLOAT b)
{
    qword r;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b.q));
    return r;
}
static inline float Length(qword value)
{
    qword d, one;
    float r;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(d), "=&j"(one) : "j"(value), "j"(value));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(r) : "r"(d));
    return r;
}
static inline void Query(LASER *owner, LASERPAIR *entry, U (&points)[2], float &distance)
{
    func_001DEF98(owner, entry, &points[0].q, &distance);
}

// name: SafeHouse port (CollectLaserDraws)
extern "C" void CollectLaserDraws__FP3ALO(LASER *plaser)
{
    RenderSoSelf(plaser);
    OXA *bound = plaser->poxa;
    if (!bound) return;
    CAMERA *cam = &g_cm;
    qword boundPosition = bound->posCenter.q;
    VU_FLOAT radius(&bound->sRadius, 0);
    qword relativePosition = Subtract(boundPosition, cam->position.q);
    if (!FInsideCmPlanes(cam, relativePosition, radius)) return;
    U points[2];
    M3 basis;
    float dist;
    for (int i = 0; i < plaser->cpair;) {
        LASERPAIR *entry = &plaser->apair[i];
        Query(plaser, entry, points, dist);
        if (entry->sVisible < dist) {
            float ratio = entry->sVisible / dist;
            points[1].q = Add(Scale(points[0].q, VU_FLOAT(1.0f - ratio)), Scale(points[1].q, VU_FLOAT(ratio)));
        }
        if (plaser->paloLine) AppendLaserLine(plaser->paloLine, points[0].q, points[1].q, 1.0f, 1.0f);
        qword dir;
        if (plaser->paloStretch || plaser->acap[0].palo || plaser->acap[1].palo) {
            dir = Subtract(points[1].q, points[0].q);
            basis = BuildLookAtMatrix(dir, g_normalZ);
        }
        if (plaser->paloStretch) {
            float length = Length(dir);
            if (0.01f < length) {
                U scale;
                scale.f[0] = length * 0.01f;
                scale.f[1] = 1.0f;
                scale.f[2] = 1.0f;
                M4 render;
                render = func_0011C210(points[0].q, &basis, &scale);
                AppendAloExtraDraws(plaser->paloStretch, &render, 1.0f, 1.0f);
            }
        }
        int next = i + 1;
        M4 matrix;
        for (unsigned int j = 0; j < 2; j++) {
            CAP *end = &plaser->acap[j];
            if (end->palo) {
                if (end->pevalScale) {
                    U scale;
                    EVAL *hook = end->pevalScale;
                    VTENT &callback = hook->vt[3];
                    ((void (*)(void *, U *, int, float, float))callback.pfn)(VT_THIS(hook, &callback), &scale, 0, end->pasega->t, end->pasega->svt);
                    matrix = func_0011C210(points[j].q, &basis, &scale);
                } else {
                    M4 *pm = &matrix;
                    func_00256D18(&matrix.rows[3].q, points[j].q);
                    matrix.rows[0] = basis.rows[0]; pm->rows[1] = basis.rows[1]; pm->rows[2] = basis.rows[2];
                    matrix.rows[0].bits[3] = matrix.rows[1].bits[3] = matrix.rows[2].bits[3] = 0;
                    pm->rows[3].f[3] = 1.0f;
                }
                AppendAloExtraDraws(end->palo, &matrix, 1.0f, 1.0f);
            }
        }
        i = next;
    }
}
