typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { U rows[3]; };
struct LM { float min, max; };
struct CLOCK { float t, dt; };
struct BINDING { char pad0[0x28]; float pitch; };
struct P;
struct ATTACH {
    char pad0[0x20]; void *binding; char pad24[0xC]; void *mesh; BINDING *meshBinding; int pad38; P *anchor;
    char pad40[0x3C]; float radius; int tactic; void *constraint; LM enterRange, exitRange, fireInterval;
};
struct PATH { char pad0[0xE8]; int count; int padEC, padF0; U *points; };
struct HIT { U start, end, normal0, normal1; float startFraction, endFraction; char pad48[0x18]; };
struct P {
    char pad0[0x188]; int state; char pad18C[0x36C]; int attachCount; ATTACH *attachments[8]; float slip;
    char pad520[0x20]; float heading, goalHeading, steering, wheelAngle, drive; char pad554[0x50];
    P *target; void *navigator; PATH *path; float cursor, nextAttack; P *selectedObject; ATTACH *selectedAttach;
};
extern CLOCK D_002DDED0;
extern const qword D_002A2DA0, D_002A2DC0;
extern float D_002C20E8, D_002C20EC, D_002C20F0, D_002C20F4, D_002C20F8;
extern "C" {
qword func_001A62E8(P *);
ATTACH *func_001D2240(P *);
P *func_001D22D0(P *);
int func_0011D910(LM *, float);
void func_001D4B28(P *, int);
float func_002456F0(float);
M3 func_0011B500(qword, float);
int func_001C0960(void *, qword, qword, int, HIT *, int);
void func_001E6180(PATH *);
void func_001D2420(P *);
void func_001C02D0(void *, qword, qword, PATH *);
float func_002458F0(float, float);
M3 *func_001A6318(P *);
qword func_0022CA18(void *, void *);
float func_0011CF60(float);
void func_001F0660(void *, int);
float func_0011D448(float, float);
void func_001D2490(P *);
int func_001D4E08(ATTACH *);
int func_00227C90(void *, qword);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GetX(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { qword r; __asm__("prot3w %0, %1" : "=r"(r) : "r"(q)); return GetX(r); }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline float Length2D(qword v)
{
    qword r;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(r) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(r));
    return GetX(r);
}
static inline float Dist2D(qword a, qword b) { return Length2D(Sub(a, b)); }
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline qword Sqrt(qword v) { qword r; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(v)); return r; }
static inline qword DivideQ(qword v, qword l) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v)); return r; }
static inline qword NormalizeSafe(qword v, qword fallback)
{
    qword len = Sqrt(Dot(v, v));
    if (GetX(len) < 0.0001f)
        return fallback;
    return DivideQ(v, len);
}
static inline qword VuFloat(float g) { qword v; __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g)); return v; }
static inline qword Scale(qword g, qword v) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(g), "j"(v)); return r; }
static inline qword Rotate(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(m.rows[0].q), "j"(m.rows[1].q), "j"(m.rows[2].q), "j"(v));
    return r;
}
static inline float Max(float a, float b) { return a < b ? b : a; }
static inline float Abs(float f) { return __builtin_fabsf(f); }

extern "C" void func_001D2610(P *p)
{
    qword position = func_001A62E8(p);
    qword target = func_001A62E8(p->target);
    qword delta = Sub(target, position);
    float distance = Length2D(delta);
    p->selectedAttach = func_001D2240(p);
    if (p->selectedAttach)
        p->selectedObject = 0;
    else
        p->selectedObject = func_001D22D0(p);
    int state;
    do {
        state = p->state;
        switch (state) {
        case 0:
            if (p->selectedAttach) {
                if (func_0011D910(&p->selectedAttach->enterRange, distance))
                    func_001D4B28(p, 1);
            } else if (p->selectedObject) {
                func_001D4B28(p, 2);
            } else {
                func_001D4B28(p, 3);
            }
            break;
        case 1:
            if (!p->selectedAttach || !func_0011D910(&p->selectedAttach->exitRange, distance))
                func_001D4B28(p, 0);
            break;
        case 2:
            if (!p->selectedObject)
                func_001D4B28(p, 0);
            break;
        case 3:
            if (p->selectedAttach || p->selectedObject)
                func_001D4B28(p, 0);
            break;
        }
    } while (state != p->state);

    switch (p->state) {
    case 0: {
        float radius = p->selectedAttach->radius;
        float angle = func_002456F0(radius / Max(radius * D_002C20E8, distance));
        qword offset = Scale(VuFloat(p->selectedAttach->radius), NormalizeSafe(Sub(position, target), D_002A2DA0));
        qword goal;
        switch (p->selectedAttach->tactic) {
        case 0:
        case 1:
            goal = target;
            break;
        case 2: {
            M3 m = func_0011B500(D_002A2DC0, angle);
            goal = Add(target, Rotate(m, offset));
            break;
        }
        case 3: {
            M3 m = func_0011B500(D_002A2DC0, -angle);
            goal = Add(target, Rotate(m, offset));
            break;
        }
        case 4:
            break;
        }
        HIT hits[4];
        if (func_001C0960(p->navigator, position, goal, 4, hits, 2) == 1 &&
            hits[0].startFraction == 0.0f && hits[0].endFraction == 1.0f) {
            p->path->points[0].q = position;
            p->path->points[1].q = goal;
            p->path->count = 2;
            func_001E6180(p->path);
            func_001D2420(p);
        } else if (p->path->count < 2 || 50.0f < Dist2D(p->path->points[p->path->count - 1].q, target)) {
            func_001C02D0(p->navigator, position, target, p->path);
            func_001D2420(p);
        }
        func_001D2490(p);
        p->wheelAngle = p->heading;
        break;
    }
    case 1: {
        p->drive = 0.0f;
        p->goalHeading = p->heading;
        p->wheelAngle = func_002458F0(GetY(delta), GetX(delta));
        if (p->nextAttack < D_002DDED0.t) {
            ATTACH *attach = func_001D2240(p);
            if (attach) {
                if (attach->mesh) {
                    M3 m = *func_001A6318(attach->anchor);
                    float aim = func_002458F0(m.rows[0].f[1], m.rows[0].f[0]);
                    qword packed = func_0022CA18(attach->mesh, attach->mesh);
                    float error = Abs(func_0011CF60(aim - p->wheelAngle));
                    float pitch = GetZ(packed) - attach->meshBinding->pitch;
                    if (!(error < D_002C20EC) || !(Abs(pitch) < D_002C20F0))
                        break;
                }
                func_001F0660(attach->binding, 0x68);
                float t = D_002DDED0.t;
                p->nextAttack = t + func_0011D448(1.0f, 1.5f);
            }
        }
        break;
    }
    case 2: {
        qword object = func_001A62E8(p->selectedObject);
        if (p->path->count < 2 || 50.0f < Dist2D(p->path->points[p->path->count - 1].q, object)) {
            func_001C02D0(p->navigator, position, object, p->path);
            func_001D2420(p);
        }
        func_001D2490(p);
        p->wheelAngle = p->heading;
        break;
    }
    case 3:
        p->goalHeading = func_002458F0(-GetY(delta), -GetX(delta));
        p->wheelAngle = p->heading;
        p->drive = p->slip * 0.85f;
        break;
    }

    if (p->nextAttack < D_002DDED0.t) {
        for (int i = 0; i < p->attachCount; i++) {
            ATTACH *attach = p->attachments[i];
            if (!func_001D4E08(attach))
                continue;
            if (attach->constraint && !func_00227C90(attach->constraint, target))
                continue;
            if (0.0f < attach->enterRange.max && p->state != 1)
                continue;
            if (attach->mesh) {
                M3 m = *func_001A6318(attach->anchor);
                float aim = func_002458F0(m.rows[0].f[1], m.rows[0].f[0]);
                qword packed = func_0022CA18(attach->mesh, attach->mesh);
                float error = Abs(func_0011CF60(aim - p->wheelAngle));
                float pitch = GetZ(packed) - attach->meshBinding->pitch;
                if (D_002C20F4 < error || D_002C20F8 < Abs(pitch))
                    continue;
            }
            func_001F0660(attach->binding, 0x68);
            float t = D_002DDED0.t;
            p->nextAttack = t + func_0011D448(attach->fireInterval.min, attach->fireInterval.max);
        }
    }
}
