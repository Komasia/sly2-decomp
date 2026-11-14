// PactionSelect__FP5GUARDP2LOP9TARGETREC: pick the first enabled response ENTRY of p that accepts target (range, height, angle, optional
// line of sight), ask p's HandleSpliceEvent(0x18) about it with a CRef(true), then run the response.
// (Claude agent, T1672) MATCH from lanef10v1 with real C++ locals instead of the SLOT union and explicit calls:
// FRAME with out-of-line ctor/dtor (__10STACKSCOPE / _$_10STACKSCOPE(this, 2)), CRef(bool) with inline dtor
// (Decref), and `void *argument = (char *)entry + 0x18;` declared after the CRef.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M4 { U row[4]; };
struct VTE { short delta, pad; void *fn; };
struct NAME { unsigned identity; };
struct SCALE { char pad[0x20]; float value; };
struct LM { float low, high; };
struct ENTRY {
    char pad0[0x50];
    LM distance, height;
    char pad60[8];
    float angle, minHit;
    int lineOfSight, filter, response;
    char pad7C[0x2C];
    int enabled;
};
struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x18];
    unsigned long flags;
    char pad30[0xC];
    NAME *name;
    char pad40[0xE9C];
    ENTRY *entries[8];
    int count;
    ENTRY *current;
    float cooldown;
    char padF08[0xB4];
    int mode;
    char padFC0[4];
    SCALE *scale;
};
struct FRAME { int n; FRAME(); ~FRAME(); }; /* out-of-line ctor/dtor: __10STACKSCOPE / _$_10STACKSCOPE(this, 2) */
struct LSG { U point; char rest[0x50]; };
struct LOS { U start, end; LSG hit; };
extern "C" void Decref(void *) asm("Decref__4CRef");
struct CREF {
    int tagk, tag;
    CREF(bool f) { tagk = 0x17; tag = f; }
    ~CREF() { Decref(this); }
};
struct POLY { float a, b, c; };
#include "clock.h"
struct BASIC {
    char pad0[0xC];
    virtual void VUnk00();
    virtual void VUnk01();
    virtual void HandleSpliceEvent(unsigned symidEvent, int fPost, int cargs, void **ppvargs, CREF *pref);
};
extern "C" {
extern POLY D_002BE600;
extern LM g_lmZeroOne;
extern char g_sw[];
int FIsBasicDerivedFrom(P *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
int FTargetrecAllows(void *, P *) asm("FTargetrecAllows__FP9TARGETRECP5GUARD");
qword PosOfLo(P *) asm("PosOfLo__FP2LO");
unsigned func_001C9950(unsigned);
int FCheckLm(LM *, float) asm("FCheckLm__FP2LMf");
qword ConvertPos(P *, P *, qword) asm("ConvertPos__FP2LOT0G9VU_VECTOR");
float atan2f(float, float) asm("atan2f");
int func_00175820(void *, void *);
void func_0020FAA0(void *, qword, qword, int (*)(void *, void *), void *, int *, void ***);
int PsoHitTestLineObjects(int, qword, qword, int, void **, LSG *) asm("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
void SetGuardResponse(P *, ENTRY *, void *, qword) asm("SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR");
void SetTargetrecTimer(void *, int) asm("SetTargetrecTimer__FP9TARGETRECi");
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
/* the second "j"(v) is allocation-only (same helper as LookScore): it fixes the from/to lqc2 reloads */
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %2\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GLengthXY(qword v)
{
    return GFromVf(QwLengthXY(v));
}
static inline float GLength(qword v)
{
    return GFromVf(QwLength(v));
}
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline float GYOfQw(qword qw)
{
    float y;
    __asm__("prot3w %0, %1" : "=r"(y) : "r"(qw));
    return y;
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(qw));
    return z;
}

static inline int Blocked(LOS *line, float limit)
{
    return GLength(QwSub(line->start.q, line->hit.point.q)) < limit;
}

// name: SafeHouse port (PactionSelect)
extern "C" ENTRY *PactionSelect__FP5GUARDP2LOP9TARGETREC(P *p, P *target, void *gate)
{
    qword from, to;
    float height, distance;
    int i;

    if (p->current)
        return 0;
    if (!target)
        return 0;
    {
        int enabled = (int)(target->flags >> 60) & 1;
        if (!enabled)
            return 0;
    }
    if (g_clock.t < p->cooldown)
        return 0;
    if (FIsBasicDerivedFrom(target, 0x32)) {
        VTE *e = &target->vt[77];
        if (((int (*)(void *))e->fn)((char *)target + e->delta))
            return 0;
    }
    if (gate && !FTargetrecAllows(gate, p))
        return 0;
    from = PosOfLo(p);
    to = PosOfLo(target);
    {
        qword d = QwSub(to, from);
        distance = GLengthXY(d);
        height = GZOfQw(d);
    }
    if (func_001C9950(target->name->identity) == func_001C9950(p->name->identity))
        distance += ((unsigned)target < (unsigned)p) ? 75.0f : -75.0f;
    if ((p->mode == 8 || p->mode == 13) && p->scale) {
        float s = p->scale->value;
        distance /= s;
        height /= s;
    }
    for (i = 0; i < p->count; i++) {
        ENTRY *entry = p->entries[i];
        float angle, gain;
        if (!entry->enabled)
            continue;
        if (!FCheckLm(&entry->distance, distance))
            continue;
        if (!FCheckLm(&entry->height, height))
            continue;
        {
            qword local = ConvertPos(0, p, to);
            angle = __builtin_fabsf(atan2f(GYOfQw(local), GXOfQw(local)));
        }
        gain = D_002BE600.a + distance * (D_002BE600.b + distance * D_002BE600.c);
        {
            float lo = g_lmZeroOne.low, hi = g_lmZeroOne.high;
            if (gain < lo)
                gain = lo;
            else if (hi < gain)
                gain = hi;
        }
        if (entry->angle < gain * angle)
            continue;
        if (entry->lineOfSight) {
            FRAME frame;
            LOS line;
            int count;
            void **objects;
            line.start.q = from;
            line.end.q = to;
            func_0020FAA0(g_sw, from, to, func_00175820, entry, &count, &objects);
            if (PsoHitTestLineObjects(0, line.start.q, line.end.q, count, objects, &line.hit) &&
                Blocked(&line, entry->minHit))
                continue;
        }
        {
            CREF ref(true);
            void *argument = (char *)entry + 0x18;
            ((BASIC *)p)->HandleSpliceEvent(0x18, 0, 1, &argument, &ref);
            if (ref.tagk != 0x17 || !ref.tag)
                continue;
            if (entry->response) {
                M4 frame;
                VTE *e = &target->vt[32];
                void *owner = ((void *(*)(void *, M4 *))e->fn)((char *)target + e->delta, &frame);
                SetGuardResponse(p, entry, owner, frame.row[3].q);
                entry = 0;
                if (gate)
                    SetTargetrecTimer(gate, 3);
            }
            return entry;
        }
    }
    return 0;
}
