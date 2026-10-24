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
struct FRAME { int a[4]; };
struct LSG { U point; char rest[0x50]; };
struct LOS { U start, end; LSG hit; };
struct CREF { int tagk, tag; };
struct PROPERTY { CREF ref; M4 frame; };
union SLOT { LOS line; PROPERTY property; };
struct POLY { float a, b, c; };
struct CLOCK { float time, dt; };
extern "C" {
extern CLOCK D_002DDED0;
extern POLY D_002BE600;
extern LM D_002BBB60;
extern char D_003DD490[];
int func_00132B10(P *, int);
int func_0020A818(void *, P *);
qword func_001A62E8(P *);
unsigned func_001C9950(unsigned);
int func_0011D910(LM *, float);
qword func_001A6F00(P *, P *, qword);
float func_002458F0(float, float);
int func_00175820(void *, void *);
void func_0020FAA0(void *, qword, qword, int (*)(void *, void *), void *, int *, void ***);
int func_0014CC58(int, qword, qword, int, void **, LSG *);
void func_001AE478(FRAME *);
void func_001AE4A0(FRAME *, int);
void func_00129EC8(CREF *);
void func_0020AB68(P *, ENTRY *, void *, qword);
void func_0020A9A8(void *, int);
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
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

static inline void Release(CREF *ref)
{
    func_00129EC8(ref);
}
static inline int Blocked(LOS *line, float limit)
{
    return GLength(QwSub(line->start.q, line->hit.point.q)) < limit;
}

extern "C" ENTRY *func_001758A0(P *p, P *target, void *gate)
{
    FRAME frame;
    SLOT slot;
    int count;
    void **objects;
    void *argument;
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
    if (D_002DDED0.time < p->cooldown)
        return 0;
    if (func_00132B10(target, 0x32)) {
        VTE *e = &target->vt[77];
        if (((int (*)(void *))e->fn)((char *)target + e->delta))
            return 0;
    }
    if (gate && !func_0020A818(gate, p))
        return 0;
    from = func_001A62E8(p);
    to = func_001A62E8(target);
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
        if (!func_0011D910(&entry->distance, distance))
            continue;
        if (!func_0011D910(&entry->height, height))
            continue;
        {
            qword local = func_001A6F00(0, p, to);
            angle = __builtin_fabsf(func_002458F0(GYOfQw(local), GXOfQw(local)));
        }
        gain = D_002BE600.a + distance * (D_002BE600.b + distance * D_002BE600.c);
        {
            float lo = D_002BBB60.low, hi = D_002BBB60.high;
            if (gain < lo)
                gain = lo;
            else if (hi < gain)
                gain = hi;
        }
        if (entry->angle < gain * angle)
            continue;
        if (entry->lineOfSight) {
            func_001AE478(&frame);
            slot.line.start.q = from;
            slot.line.end.q = to;
            func_0020FAA0(D_003DD490, from, to, func_00175820, entry, &count, &objects);
            if (func_0014CC58(0, slot.line.start.q, slot.line.end.q, count, objects, &slot.line.hit) &&
                Blocked(&slot.line, entry->minHit)) {
                func_001AE4A0(&frame, 2);
                continue;
            }
            func_001AE4A0(&frame, 2);
        }
        {
        CREF *ref = &slot.property.ref;
        ref->tagk = 0x17;
        ref->tag = 1;
        {
        void **pa = &argument;
        *pa = (char *)entry + 0x18;
        {
            VTE *e = &p->vt[3];
            ((void (*)(void *, int, int, int, void **, CREF *))e->fn)((char *)p + e->delta, 0x18, 0, 1, pa, ref);
        }
        }
        if (slot.property.ref.tagk != 0x17 || !slot.property.ref.tag) {
            func_00129EC8(ref);
            continue;
        }
        }
        if (entry->response) {
            VTE *e = &target->vt[32];
            void *owner = ((void *(*)(void *, M4 *))e->fn)((char *)target + e->delta, &slot.property.frame);
            func_0020AB68(p, entry, owner, slot.property.frame.row[3].q);
            entry = 0;
            if (gate)
                func_0020A9A8(gate, 3);
        }
        Release(&slot.property.ref);
        return entry;
    }
    return 0;
}
