typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; int i[4]; } U;
typedef struct NODE {
    char pad0[0xE0];
    struct NODE *nextE0;
    char padE4[4];
    unsigned flags;
    char padEC[0x18];
    struct NODE *next104;
    char pad108[4];
    float reach;
    char pad110[0x64];
    struct NODE *next174;
    char pad178[0x3C];
    struct NODE *next1B4;
} NODE;
typedef struct PAIR { qword candidate; qword original; } PAIR;
typedef struct P {
    char pad0[0x10];
    NODE *actor;
    char pad14[0x28];
    float time;
    char pad40[0x10];
    PAIR pair[4];
    int index;
} P;
typedef struct ROW { qword point; float angle; } ROW;
typedef struct QUERY {
    qword point;
    float heading;
    int count;
    ROW row[64];
    qword candidate;
    U delta;
    qword scalar;
} QUERY;
typedef struct LM { float low, high; } LM;

extern NODE *D_003E13FC, *D_003E13F0, *D_003E1408, *D_003E13E4, *D_003E13C0, *D_003E13D8, *D_003E13CC, *D_003E13B4,
    *D_003E1450;
extern char D_003DD490[];
extern qword D_002A2DA0, D_002A2DC0;
extern float D_002A53D0;
extern LM D_002BE5A8, D_002BE5B0;
extern qword func_001A62E8(NODE *);
extern float func_00204740(NODE *);
extern void func_00172798(QUERY *);
extern void func_001E6F60(NODE *, qword, void *, qword *, void *, void *, void *);
extern int func_00132B10(NODE *, int);
extern int func_0015E9C8(void *, int, int, void *, int, NODE **);
extern int func_00172888(const void *, const void *);
extern void func_002338C0(void *, int, int, int (*)(const void *, const void *));
extern qword func_0011E1A0(float, float, float);
extern float func_0011D448(float, float);

static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword LengthXY(qword v)
{
    qword d;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Scale(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(l));
    return r;
}
static inline qword AddScaled(qword a, qword v, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s));
    return r;
}
static inline float GetX(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}
static inline qword VF(float g)
{
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g));
    return r;
}
static inline qword VFI(int g)
{
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g));
    return r;
}
/* volatile: the target re-broadcasts the constant inside the loop (loop.c must not hoist it) */
static inline qword VFV(float g)
{
    qword r;
    __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g));
    return r;
}
static inline float DistXY(qword a, qword b)
{
    a = Sub(a, b);
    return GetX(LengthXY(a));
}
static inline qword NormalizeSafe(qword v, qword def)
{
    qword len = Length(v);
    if (GetX(len) < 0.0001f)
        return def;
    return DivQ(v, len);
}

void func_001728B0(P *p)
{
    QUERY q;
    NODE *a256[256];
    NODE *a32[32];
    NODE *a128[128];
    U origin;
    U anchor;
    NODE *o;
    int n;
    unsigned c;
    float lastAngle;
    PAIR *prev;
    PAIR *pair;

    q.point = func_001A62E8(p->actor);
    q.heading = func_00204740(p->actor);
    q.count = 0;
    for (o = D_003E13FC; o; o = o->next104) {
        qword pos = func_001A62E8(o);
        qword s;
        q.delta.q = Sub(q.point, pos);
        q.delta.f[2] = 0.0f;
        s = VFI(*(int *)&o->reach);
        q.scalar = s;
        q.candidate = AddScaled(pos, NormalizeSafe(q.delta.q, D_002A2DA0), s);
        func_00172798(&q);
    }
    for (o = D_003E13F0; o; o = o->next1B4) {
        func_001E6F60(o, q.point, 0, &q.candidate, 0, 0, 0);
        func_00172798(&q);
    }
    for (o = D_003E1408; o; o = o->next104) {
        q.candidate = func_001A62E8(o);
        func_00172798(&q);
    }
    for (o = D_003E13E4; o; o = o->next174) {
        q.candidate = func_001A62E8(o);
        func_00172798(&q);
    }
    for (o = D_003E13C0; o; o = o->next1B4) {
        func_001E6F60(o, q.point, 0, &q.candidate, 0, 0, 0);
        func_00172798(&q);
    }
    for (o = D_003E13D8; o; o = o->next104) {
        q.candidate = func_001A62E8(o);
        func_00172798(&q);
    }
    for (o = D_003E13CC; o; o = o->next1B4) {
        func_001E6F60(o, q.point, 0, &q.candidate, 0, 0, 0);
        func_00172798(&q);
    }
    for (o = D_003E13B4; o; o = o->nextE0) {
        if ((o->flags & 1) && func_00132B10(o, 0x13)) {
            q.candidate = func_001A62E8(o);
            func_00172798(&q);
        }
    }
    {
    int i;
    n = func_0015E9C8(D_003DD490, 0x505, 0x23, 0, 0x100, a256);
    for (i = 0; i < n; i++) {
        q.candidate = func_001A62E8(a256[i]);
        func_00172798(&q);
    }
    n = func_0015E9C8(D_003DD490, 0x505, 0x67, 0, 0x20, a32);
    for (i = 0; i < n; i++) {
        q.candidate = func_001A62E8(a32[i]);
        func_00172798(&q);
    }
    n = func_0015E9C8(D_003DD490, 0x505, 0x1B, 0, 0x80, a128);
    for (i = 0; i < n; i++) {
        q.candidate = func_001A62E8(a128[i]);
        func_00172798(&q);
    }
    }
    for (o = D_003E1450; o; o = o->next174) {
        q.candidate = func_001A62E8(o);
        func_00172798(&q);
    }

    lastAngle = 0.0f;
    func_002338C0(q.row, q.count, sizeof(ROW), func_00172888);
    c = 0;
    {
        int i;
        prev = 0;
        for (i = 0; i < q.count && c < 4; i++) {
            ROW *row = &q.row[i];
            qword pt = row->point;
            qword d = Sub(pt, q.point);
            qword up = D_002A2DC0;
            qword planar = Sub(d, Scale(up, Dot(d, up)));
            qword nrm = NormalizeSafe(planar, D_002A2DA0);
            qword s = VFV(200.0f);
            qword t = AddScaled(q.point, nrm, s);
            q.delta.q = s;
            if (prev && DistXY(t, prev->candidate) < 150.0f)
                continue;
            prev = &p->pair[c];
            lastAngle = row->angle;
            c++;
            prev->original = pt;
            prev->candidate = t;
        }
    }
    origin.q = q.point;
    anchor.q = Add(origin.q, func_0011E1A0(q.heading + 3.1415927f, -350.0f, 0.0f));
    while (c < 4) {
        float angle, length;
        qword v;
        lastAngle += func_0011D448(D_002BE5A8.low, D_002BE5A8.high);
        angle = lastAngle + q.heading;
        length = func_0011D448(D_002BE5B0.low, D_002BE5B0.high);
        v = Add(anchor.q, func_0011E1A0(angle, length, 0.0f));
        p->pair[c].original = v;
        p->pair[c].candidate = v;
        c++;
    }
    p->index = 0;
    p->time = D_002A53D0;
}
