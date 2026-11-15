// AddLaserContacts__FP3ALOP3SOEiiiPP2XP: for every beam of the laser, find where the segment between its two endpoints hits the other shape entry (first
// ClipSegmentSoe, else the shape test FIsBasicDerivedFrom + HitStepSupport) and add a kind-10 contact there with PxpAdd
// (PxpAddSw), then post the LASER::Notify (ApplyLaserContacts__FP3ALO) message through PostDeferredCall.
// What mattered (w3lane2):
//  - the same 6-argument virtual signature as AddSwarmXps / MarkProjectileSweep, with every argument passed through to
//    the empty base stub func_001F5990 (no code, but the call's argument uses fix the prologue schedule);
//  - VU helpers taking VU_VECTOR parameters (const qword & conversion): the extra RTL copies keep the loop above
//    loop.c's ~95-insn limit, so i * sizeof(LASERPAIR) stays a mult inside the loop as in the target;
//  - Len(v) = Sqrt(Dot(v, v)) with a two-input Dot, one asm per VU step (target VU order and vf registers);
//  - the distance is a float in a GPR (qmfc2) passed bit-for-bit as PxpAdd's int argument (v0 scratch, not v1).
#include "h3_laser.h"
#include "cid.h"
struct LASER {
    char pad0[0xE4];
    void *psoe;          // SO +0xE4: the laser's shape entry (its single bound)
    char padE8[0x198 - 0xE8];
    int cpair;
    LASERPAIR *apair;
    void Notify() __asm__("ApplyLaserContacts__FP3ALO");
};
struct SUB { char pad[0x14]; void **ppalo; };
struct SOE { int x0; SUB *psub; };   // the other object's shape entry (psub->ppalo: its object, SafeHouse other->palo)

struct HIT { qword pos; char pad[0x50]; };
union VECTOR { qword q; float f[4]; };
struct G;
extern G g_sw;
typedef void (LASER::*PMF)();
extern "C" {
void func_001F5990(LASER *, SOE *, int, int, int, XP **);
void func_001DEF98(LASER *, LASEREND *, qword *, float *);
int ClipSegmentSoe(SOE *, qword, qword, int, HIT *) asm("ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG");
int FIsBasicDerivedFrom(void *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
int HitStepSupport(void *, qword, qword, qword *) asm("HitStepSupport__FP3ALOG9VU_VECTORT1P6VECTOR");
void PxpAddSw(G *, void *, SOE *, qword, qword, int, int, int, XP **, float) asm("PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf");   // PxpAdd
void PostDeferredCall(G *, LASER *, PMF, int) asm("PostDeferredCall__FPvUi15PFNDEFERREDCALLi");
}

struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, VU_VECTOR b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q));
    return d;
}
static inline qword Dot(VU_VECTOR a, VU_VECTOR b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a.q), "j"(b.q));
    return d;
}
static inline qword Sqrt(VU_VECTOR d)
{
    qword l;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d.q));
    return l;
}
static inline qword Len(VU_VECTOR v) { return Sqrt(Dot(v, v)); }
static inline qword Div(VU_VECTOR v, VU_VECTOR l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l.q), "j"(v.q));
    return r;
}
static inline float Scalar(VU_VECTOR v)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v.q));
    return f;
}

// name: SafeHouse port (AddLaserContacts)
extern "C" void AddLaserContacts__FP3ALOP3SOEiiiPP2XP(LASER *plaser, SOE *psoeOther, int a2, int a3, int a4, XP **pout)
{
    int i;
    func_001F5990(plaser, psoeOther, a2, a3, a4, pout);
    for (i = 0; i < plaser->cpair; i++) {
        LASERPAIR *ppair = &plaser->apair[i];
        qword seg[2];   // the beam's endpoints
        VECTOR pos;
        HIT hit;
        int found = 0;
        func_001DEF98(plaser, ppair->aend, seg, 0);
        if (!ClipSegmentSoe(psoeOther, seg[0], seg[1], 1, &hit)) {
            void *so = *psoeOther->psub->ppalo;   // the object owning the other shape
            if (FIsBasicDerivedFrom(so, CID_STEP))
                found = HitStepSupport(so, seg[0], seg[1], &pos.q);
        } else {
            found = 1;
            pos.q = hit.pos;
        }
        if (found) {
            float dist = Scalar(Len(Sub(seg[0], pos.q)));
            qword dir = Sub(seg[1], seg[0]);
            dir = Div(dir, Len(dir));
            PxpAddSw(&g_sw, plaser->psoe, psoeOther, pos.q, dir, 10, *(int *)&dist, 0, &ppair->pxpFirst, 0.0f);
            PostDeferredCall(&g_sw, plaser, &LASER::Notify, 0);
        }
    }
}
