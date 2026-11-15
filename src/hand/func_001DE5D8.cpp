// BindEnd__FP3ALO: (re)builds the endpoint state of every beam of the laser (h3_laser.h) and its bounding box. Each
// beam has two endpoints; an endpoint names an object: a path (CID_PATH) becomes a moving endpoint with a 1/2/6-segment
// motion profile (LASERMODE_Wrap / Stop / PingPong, the last a trapezoidal accelerate-cruise-decelerate profile),
// XFM / SO objects and missing objects become fixed points. All points (or the whole transformed path) are accumulated
// into a min/max box that becomes the laser's single bound (CopyTransformGeom copies it to world space).
// Fresh rewrite (wave-4 lane 9).
// What mattered:
//  - Min/Max take VU_VECTOR (const qword & conversion) parameters as in AddLaserContacts: the extra RTL copies keep the
//    endpoint loop large enough that loop.c does not hoist 1.0f and 16 out of it;
//  - the min/max initializers are non-const globals (const loads may be scheduled above the spill stores);
//  - every segment is addressed as seg = &endpoint->track.motion.aseg[k] (the store to the first field folds to
//    an endpoint-relative address), fields stored in struct order;
//  - the search loop reuses `seg` (set many times, so sched1 does not boost its sets), which lets `next` take $v0;
//  - the bound points are written through a block-local pointer so the address is loaded before each call.
#include "vtbl.h"
#include "h3_laser.h"
#include "cid.h"
typedef unsigned long ulong;
typedef unsigned int uint;

struct M4 { qword rows[4]; };
struct CRV {        // path (class 10): its points (count, points) and the matrix callback (vt slot 31)
    char pad0[0xC];
    VTENT *vt;
    char pad10[0xE8 - 0x10];
    int count;
    int padEC;
    void *padF0;
    qword *points;
};
union U { qword q; float f[4]; };
struct GEO { int count; U *points; int planeCount; void *planes; int edgeCount; void *edges; };
struct LASER;
struct BOUND {
    void *object;
    LASER *owner;
    float radius;
    int tag;
    ulong flags;
    int id, pinned;
    M4 matrix;
    char pad60[8];
    int tree[4];
    GEO local, world;
    int state, stamp;
};
struct LASER {       // the SO base fields this function uses, then the laser's beams
    char pad0[0xC];
    VTENT *vt;
    char pad10[8];
    int id;
    char pad1C[0xC];
    ulong flags28;
    char pad30[0x10];
    uint flags;
    char pad44[0x1C];
    void *space;
    char pad64[0xE0 - 0x64];
    int boundCount;
    BOUND *bounds;
    char padE8[0x198 - 0xE8];
    int cpair;
    LASERPAIR *apair;
};
struct MSG { int bytes, alignment; };
struct G;
extern G g_sw;
extern qword D_002A2DF0, D_002A2E00;   // the empty box's initial minimum / maximum (+/- FLT_MAX)
extern float D_002C3610;               // PingPong easing distance (100.0)
extern "C" {
void RemoveAloSoes(LASER *) asm("RemoveAloSoes__FP3ALO");
void *PloFindSwNearest(G *, int, int, LASER *) asm("PloFindSwNearest__FP2LO3OIDii");
int FIsBasicDerivedFrom(void *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
float SMaxCrv(CRV *) asm("SMaxCrv__FP3CRV");
void EvalCrvS(CRV *, qword *, qword *, float) asm("EvalCrvS__FP3CRVfP6VECTORT2");
void *s1_memset(void *, int, int) asm("memset");
qword PosOfLo(void *) asm("PosOfLo__FP2LO");
qword PosConvertXfs(void *, void *, qword) asm("PosConvertXfs__FP2XFT0G9VU_VECTOR");
void *PvAllocSwClearImpl(MSG *) asm("PvAllocSwClearImpl__Fi");
void CopyTransformGeom(GEO *, const M4 *, GEO *) asm("CopyTransformGeom__FP4GEOMP7MATRIX4T0");
void AddAloSoes(LASER *) asm("AddAloSoes__FP3ALO");
}

struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Min(VU_VECTOR a, VU_VECTOR b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q)); return r; }
static inline qword Max(VU_VECTOR a, VU_VECTOR b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q)); return r; }
static inline qword Transform(const M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m->rows[0]), "j"(m->rows[1]), "j"(m->rows[2]), "j"(m->rows[3]), "j"(p));
    return r;
}
static inline float Clamp(float f, float low, float high) { if (f < low) return low; else if (high < f) return high; else return f; }
static inline M4 *GetMatrix(CRV *path) { VTENT *v = &path->vt[31]; return ((M4 * (*)(void *))v->pfn)(VT_THIS(path, v)); }
static inline void SetDirty(LASER *p) { uint f = p->flags; if ((f ^ 1) & 1) *(uint *)f |= 2; else p->flags = f | 2; }

// name: SafeHouse port (BindEnd)
extern "C" void BindEnd__FP3ALO(LASER *p)
{
    int i;
    qword minimum, maximum;
    RemoveAloSoes(p);
    minimum = D_002A2DF0;
    maximum = D_002A2E00;
    for (i = 0; i < p->cpair; i++) {
        LASERPAIR *entry = &p->apair[i];
        uint j;
        for (j = 0; j < 2; j++) {
            LASEREND *endpoint = &entry->aend[j];
            endpoint->kind = LASERENDK_Nil;
            if (endpoint->oid != -1) {
                void *object = PloFindSwNearest(&g_sw, 1, endpoint->oid, p);
                if (object) {
                    if (FIsBasicDerivedFrom(object, CID_PATH)) {
                        CRV *path = (CRV *)object;
                        LASERPARAMS params = endpoint->track.params;
                        int reverse = 0;
                        params.fraction = Clamp(params.fraction, 0.0f, 1.0f);
                        if (params.speed < 0.0f) { reverse = 1; params.speed = -params.speed; }
                        params.duration = __builtin_fabsf(params.duration);
                        if (params.mode != LASERMODE_Wrap && params.mode != LASERMODE_PingPong && params.mode != LASERMODE_Stop) params.mode = LASERMODE_Wrap;
                        float length = SMaxCrv(path);
                        if (0.0f < params.duration) params.speed = length / params.duration;
                        else if (0.0f < params.speed) params.duration = length / params.speed;
                        float start = params.fraction * length;
                        if (params.speed == 0.0f || params.duration == 0.0f) {
                            endpoint->kind = LASERENDK_Point;
                            EvalCrvS(path, &endpoint->pos, 0, start);
                        } else {
                            endpoint->track.pcrv = path;
                            endpoint->kind = LASERENDK_Path;
                            endpoint->track.s = start;
                            s1_memset(endpoint->track.motion.aseg, 0, sizeof(endpoint->track.motion.aseg));
                            LASERSEG *seg;
                            switch (params.mode) {
                            case LASERMODE_Wrap:
                                endpoint->track.motion.cseg = 1;
                                seg = endpoint->track.motion.aseg;
                                if (reverse) {
                                    seg->start = length;
                                    seg->speed = -params.speed;
                                    seg->elapsed = (1.0f - params.fraction) * params.duration;
                                } else {
                                    seg->speed = params.speed;
                                    seg->elapsed = params.fraction * params.duration;
                                }
                                seg->duration = params.duration;
                                endpoint->track.motion.iseg = 0;
                                break;
                            case LASERMODE_Stop:
                                endpoint->track.motion.cseg = 2;
                                seg = endpoint->track.motion.aseg;
                                if (reverse) {
                                    seg->start = length;
                                    seg->speed = -params.speed;
                                    seg->elapsed = (1.0f - params.fraction) * params.duration;
                                } else {
                                    seg->speed = params.speed;
                                    seg->elapsed = params.fraction * params.duration;
                                }
                                seg->duration = params.duration;
                                seg = &endpoint->track.motion.aseg[1];
                                if (reverse) seg->start = 0.0f;
                                else seg->start = length;
                                seg->speed = 0.0f;
                                seg->elapsed = 0.0f;
                                endpoint->track.motion.iseg = 0;
                                break;
                            case LASERMODE_PingPong: {
                                struct { float in, out; } ramp;
                                if (3.0f * D_002C3610 <= length) ramp.in = D_002C3610;
                                else ramp.in = length * 0.2f;
                                float twice = ramp.in + ramp.in;
                                ramp.out = length - ramp.in;
                                float rampTime = twice * params.duration / (length + twice);
                                float middleTime = params.duration - (rampTime + rampTime);
                                params.speed = (length - twice) / middleTime;
                                float accel = params.speed * params.speed / twice;
                                endpoint->track.motion.cseg = 6;
                                seg = endpoint->track.motion.aseg;
                                seg->accel = accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.aseg[1];
                                seg->start = ramp.in;
                                seg->speed = params.speed;
                                seg->duration = middleTime;
                                seg = &endpoint->track.motion.aseg[2];
                                seg->start = ramp.out;
                                seg->speed = params.speed;
                                seg->accel = -accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.aseg[3];
                                seg->start = length;
                                seg->accel = -accel;
                                seg->duration = rampTime;
                                seg = &endpoint->track.motion.aseg[4];
                                seg->start = ramp.out;
                                seg->speed = -params.speed;
                                seg->duration = middleTime;
                                seg = &endpoint->track.motion.aseg[5];
                                seg->start = ramp.in;
                                seg->speed = -params.speed;
                                seg->accel = accel;
                                seg->duration = rampTime;
                                // find the segment the start position falls in and the time already spent in it
                                for (endpoint->track.motion.iseg = 0; endpoint->track.motion.iseg < 3; endpoint->track.motion.iseg++) {
                                    seg = &endpoint->track.motion.aseg[endpoint->track.motion.iseg];
                                    LASERSEG *next = seg + 1;
                                    if (start < next->start) {
                                        float t = ((start - seg->start) + (start - seg->start)) / (seg->speed + next->speed);
                                        if (reverse) {
                                            int k = 5 - endpoint->track.motion.iseg;
                                            endpoint->track.motion.iseg = k;
                                            seg = &endpoint->track.motion.aseg[k];
                                            seg->elapsed = seg->duration - t;
                                        } else {
                                            seg->elapsed = t;
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                            }
                            SetDirty(p);
                        }
                    } else if (FIsBasicDerivedFrom(object, CID_XFM) || FIsBasicDerivedFrom(object, CID_SO)) {
                        endpoint->kind = LASERENDK_Point;
                        endpoint->pos = PosOfLo(object);
                    }
                }
            }
            if (endpoint->kind == LASERENDK_Nil) {
                endpoint->kind = LASERENDK_Point;
                endpoint->pos = PosOfLo(p);
            }
            switch (endpoint->kind) {
            case LASERENDK_Point:
                minimum = Min(minimum, endpoint->pos);
                maximum = Max(maximum, endpoint->pos);
                endpoint->pos = PosConvertXfs(0, p->space, endpoint->pos);
                break;
            case LASERENDK_Path: {
                // the matrix callback may change the endpoint's path, so it is re-read
                M4 matrix = *GetMatrix(endpoint->track.pcrv);
                int k;
                for (k = 0; k < endpoint->track.pcrv->count; k++) {
                    qword point = Transform(&matrix, endpoint->track.pcrv->points[k]);
                    minimum = Min(minimum, point);
                    maximum = Max(maximum, point);
                }
                break;
            }
            }
        }
    }
    if (p->cpair) {
        MSG request;
        p->boundCount = 1;
        request.bytes = sizeof(BOUND);
        request.alignment = 16;
        BOUND *bound = (BOUND *)PvAllocSwClearImpl(&request);
        p->bounds = bound;
        bound->object = p->space;
        bound->owner = p;
        bound->tag = p->id;
        bound->flags |= 1UL << 48;
        bound->local.count = 2;
        request.alignment = 16;
        request.bytes = 2 * sizeof(qword);
        bound->local.points = (U *)PvAllocSwClearImpl(&request);
        CopyTransformGeom(&bound->local, 0, &bound->world);
        bound->world.points[0].q = minimum;
        bound->world.points[1].q = maximum;
        { U *out = bound->local.points; out[0].q = PosConvertXfs(0, p->space, minimum); }
        { U *out = bound->local.points; out[1].q = PosConvertXfs(0, p->space, maximum); }
    }
    if ((int)(p->flags28 >> 60) & 1) AddAloSoes(p);
}
