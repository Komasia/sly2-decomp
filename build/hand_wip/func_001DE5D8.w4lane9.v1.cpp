typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
typedef unsigned int uint;

struct VTE { short delta, pad; void *fn; };
struct M4 { qword rows[4]; };
struct PATH {
    char pad0[0xC];
    VTE *vt;
    char pad10[0xE8 - 0x10];
    int count;
    int padEC;
    void *padF0;
    qword *points;
};
struct PARAMS { float fraction, speed, duration; int mode; };
struct SEGMENT { float start, speed, accel, duration, elapsed; };
struct MOTION { int count; SEGMENT segments[6]; int current; };
struct TRACK { PATH *path; float cursor; union { PARAMS params; MOTION motion; }; };
struct ENDPOINT { int id, kind; int pad8[2]; union { qword point; TRACK track; }; };
struct ENTRY { ENDPOINT endpoints[2]; char pad140[0x10]; };
struct GEO { int count; qword *points; int planeCount; void *planes; int edgeCount; void *edges; };
struct P;
struct BOUND {
    void *object;
    P *owner;
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
struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[8];
    int id;
    char pad1C[0xC];
    ulong low : 60;
    ulong attached : 1;
    ulong high : 3;
    char pad30[0x10];
    uint flags;
    char pad44[0x1C];
    void *space;
    char pad64[0xE0 - 0x64];
    int boundCount;
    BOUND *bounds;
    char padE8[0x198 - 0xE8];
    int count;
    ENTRY *entries;
};
struct MSG { int bytes, alignment; };
struct G;
extern G D_003DD490;
extern const qword D_002A2DF0, D_002A2E00;
extern float D_002C3610;
extern "C" {
void func_001F2BA8(P *);
void *func_0015E938(G *, int, int, P *);
int func_00132B10(void *, int);
float func_001E6648(PATH *);
void func_001E6F10(PATH *, qword *, qword *, float);
void *func_002333B4(void *, int, int);
qword func_001A62E8(void *);
qword func_0022FC48(void *, void *, qword);
void *func_001AE2A0(MSG *);
void func_00166270(GEO *, const M4 *, GEO *);
void func_001F2B20(P *);
}

static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Transform(const M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m->rows[0]), "j"(m->rows[1]), "j"(m->rows[2]), "j"(m->rows[3]), "j"(p));
    return r;
}
static inline M4 *GetMatrix(PATH *path) { VTE *v = &path->vt[31]; return ((M4 * (*)(void *))v->fn)((char *)path + v->delta); }
static inline void SetDirty(P *p) { uint f = p->flags; if ((f ^ 1) & 1) *(uint *)f |= 2; else p->flags = f | 2; }

extern "C" void func_001DE5D8(P *p)
{
    int i;
    qword minimum, maximum;
    func_001F2BA8(p);
    minimum = D_002A2DF0;
    maximum = D_002A2E00;
    for (i = 0; i < p->count; i++) {
        ENTRY *entry = &p->entries[i];
        uint j;
        for (j = 0; j < 2; j++) {
            ENDPOINT *endpoint = &entry->endpoints[j];
            endpoint->kind = -1;
            if (endpoint->id != -1) {
                void *object = func_0015E938(&D_003DD490, 1, endpoint->id, p);
                if (object) {
                    if (func_00132B10(object, 10)) {
                        PATH *path = (PATH *)object;
                        PARAMS params = endpoint->track.params;
                        int reverse = 0;
                        if (params.fraction < 0.0f) params.fraction = 0.0f;
                        else if (1.0f < params.fraction) params.fraction = 1.0f;
                        if (params.speed < 0.0f) { reverse = 1; params.speed = -params.speed; }
                        params.duration = __builtin_fabsf(params.duration);
                        if (params.mode != 8 && params.mode != 16 && params.mode != 0) params.mode = 8;
                        float length = func_001E6648(path);
                        if (0.0f < params.duration) params.speed = length / params.duration;
                        else if (0.0f < params.speed) params.duration = length / params.speed;
                        float start = params.fraction * length;
                        if (params.speed == 0.0f || params.duration == 0.0f) {
                            endpoint->kind = 0;
                            func_001E6F10(path, &endpoint->point, 0, start);
                        } else {
                            endpoint->track.path = path;
                            endpoint->kind = 1;
                            endpoint->track.cursor = start;
                            SEGMENT *segments = endpoint->track.motion.segments;
                            func_002333B4(segments, 0, sizeof(endpoint->track.motion.segments));
                            switch (params.mode) {
                            case 8:
                                endpoint->track.motion.count = 1;
                                if (reverse) {
                                    segments[0].start = length;
                                    segments[0].speed = -params.speed;
                                    segments[0].elapsed = (1.0f - params.fraction) * params.duration;
                                } else {
                                    segments[0].speed = params.speed;
                                    segments[0].elapsed = params.fraction * params.duration;
                                }
                                segments[0].duration = params.duration;
                                endpoint->track.motion.current = 0;
                                break;
                            case 0:
                                endpoint->track.motion.count = 2;
                                if (reverse) {
                                    segments[0].start = length;
                                    segments[0].speed = -params.speed;
                                    segments[0].elapsed = (1.0f - params.fraction) * params.duration;
                                } else {
                                    segments[0].speed = params.speed;
                                    segments[0].elapsed = params.fraction * params.duration;
                                }
                                segments[0].duration = params.duration;
                                if (reverse) segments[1].start = 0.0f;
                                else segments[1].start = length;
                                segments[1].elapsed = 0.0f;
                                segments[1].speed = 0.0f;
                                endpoint->track.motion.current = 0;
                                break;
                            case 16: {
                                float ramp[2];
                                if (3.0f * D_002C3610 <= length) ramp[0] = D_002C3610;
                                else ramp[0] = length * 0.2f;
                                float twice = ramp[0] + ramp[0];
                                ramp[1] = length - ramp[0];
                                float rampTime = twice * params.duration / (length + twice);
                                float middleTime = params.duration - (rampTime + rampTime);
                                params.speed = (length - twice) / middleTime;
                                float accel = params.speed * params.speed / twice;
                                endpoint->track.motion.count = 6;
                                segments[0].duration = rampTime;
                                segments[0].accel = accel;
                                segments[1].start = ramp[0];
                                segments[1].duration = middleTime;
                                segments[1].speed = params.speed;
                                segments[2].start = ramp[1];
                                segments[2].duration = rampTime;
                                segments[2].speed = params.speed;
                                segments[2].accel = -accel;
                                segments[3].start = length;
                                segments[3].duration = rampTime;
                                segments[3].accel = -accel;
                                segments[4].start = ramp[1];
                                segments[4].duration = middleTime;
                                segments[4].speed = -params.speed;
                                segments[5].start = ramp[0];
                                segments[5].duration = rampTime;
                                segments[5].accel = accel;
                                segments[5].speed = -params.speed;
                                for (endpoint->track.motion.current = 0; endpoint->track.motion.current < 3; endpoint->track.motion.current++) {
                                    SEGMENT *seg = &segments[endpoint->track.motion.current];
                                    if (start < seg[1].start) {
                                        float t = ((start - seg->start) + (start - seg->start)) / (seg->speed + seg[1].speed);
                                        if (reverse) {
                                            int k = 5 - endpoint->track.motion.current;
                                            endpoint->track.motion.current = k;
                                            segments[k].elapsed = segments[k].duration - t;
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
                    } else if (func_00132B10(object, 3) || func_00132B10(object, 0x30)) {
                        endpoint->kind = 0;
                        endpoint->point = func_001A62E8(object);
                    }
                }
            }
            if (endpoint->kind == -1) {
                endpoint->kind = 0;
                endpoint->point = func_001A62E8(p);
            }
            switch (endpoint->kind) {
            case 0:
                minimum = Min(minimum, endpoint->point);
                maximum = Max(maximum, endpoint->point);
                endpoint->point = func_0022FC48(0, p->space, endpoint->point);
                break;
            case 1: {
                M4 matrix = *GetMatrix(endpoint->track.path);
                int k;
                for (k = 0; k < endpoint->track.path->count; k++) {
                    qword point = Transform(&matrix, endpoint->track.path->points[k]);
                    maximum = Max(maximum, point);
                    minimum = Min(minimum, point);
                }
                break;
            }
            }
        }
    }
    if (p->count) {
        MSG request;
        p->boundCount = 1;
        request.bytes = sizeof(BOUND);
        request.alignment = 16;
        BOUND *bound = (BOUND *)func_001AE2A0(&request);
        p->bounds = bound;
        bound->object = p->space;
        bound->owner = p;
        bound->tag = p->id;
        bound->flags |= 1UL << 48;
        bound->local.count = 2;
        request.bytes = 2 * sizeof(qword);
        request.alignment = 16;
        bound->local.points = (qword *)func_001AE2A0(&request);
        func_00166270(&bound->local, 0, &bound->world);
        bound->world.points[0] = minimum;
        bound->world.points[1] = maximum;
        bound->local.points[0] = func_0022FC48(0, p->space, minimum);
        bound->local.points[1] = func_0022FC48(0, p->space, maximum);
    }
    if (p->attached) func_001F2B20(p);
}
