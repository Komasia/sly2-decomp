// func_00178EE0 laneG4v1 (Claude agent, 2026-10-24): fresh plain-C rewrite from the asm, NO pins, aligned 68 (frame 0x80 vs 0x70).
// position is a spilled pseudo (struct VEC return) = target's 0x10; delta is caller-saved in vf4 in case 3 like the target, but in
// case 0 CSE uses an inline-parameter copy of delta (pseudo set right after Reject, spilled to 0x20) -> extra slot. Left: that copy,
// clamp load order, case-3 fallback D_002A2DD0 via lq+qmtc2, 754/750-style scheduling.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct M4 { qword r[4]; };
struct ACTOR { char pad[0xFD0]; char control[1]; };
struct MODEL { char pad[0x10]; qword velocity; };
struct CONTROL { char pad[0x24]; void *animation; };
struct CHOICE { int kind; struct MODEL *model; struct CONTROL *control; };
struct DRIVER { char pad[0x40]; struct CHOICE *choice; };
struct P {
    char pad[0x10]; struct ACTOR *actor; int pad14; struct DRIVER *driver;
    char pad1C[0x4C - 0x1C]; unsigned int mode; char pad50[0x80 - 0x50]; qword target;
    char pad90[0xC4 - 0x90]; float rate; char padC8[8]; qword cached; float timeout;
};
struct POLY { float a, b, c; };
struct LIMIT { float low, high; };
struct CLOCK { float t, dt; };
extern struct POLY D_002BE6A0;
extern struct LIMIT D_002BBB60;
extern float D_002BE694, D_002BE6B0;
extern struct CLOCK D_002DDED0;
extern qword D_002A2DC0, D_002A2DD0;
void func_001789F8(struct P *);
struct VEC { qword q; };
struct VEC func_001A62E8(struct ACTOR *);
struct M4 *func_001A6318(struct ACTOR *);
void func_00131A00(void *, float);
float func_002458F0(float, float);
void func_00209818(void *, float);
void func_0020CB28(struct CONTROL *, qword);

static __inline__ qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(r), "=&j"(one) : "j"(a), "j"(b));
    return r;
}
static __inline__ qword ScaleX(qword v, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static __inline__ qword LenSqXY(qword a) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(a)); return r; }
static __inline__ qword Sqrt(qword a) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(a)); return r; }
static __inline__ qword Bits(qword a) { qword r; __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(a)); return r; }
static __inline__ float X(qword a) { float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(a)); return f; }
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ qword Reject(qword v, qword up) { return Sub(v, ScaleX(up, Dot(v, up))); }
static __inline__ float LengthXY(qword v) { return X(Sqrt(LenSqXY(v))); }
static __inline__ float Length(qword v) { return X(Sqrt(Dot(v, v))); }
static __inline__ qword Project(struct M4 *m, qword v)
{
    qword x, y, z, one, r;
    __asm__("vmul.xyzw %0,%5,%8\n\tvmaxw.xyzw %3,$vf0,$vf0w\n\tvmul.xyzw %1,%6,%8\n\tvmul.xyzw %2,%7,%8\n\t"
            "vadday.x $ACC,%0,%0y\n\tvmaddz.x %4,%3,%0z\n\tvaddax.y $ACC,%1,%1x\n\tvmaddz.y %4,%3,%1z\n\t"
            "vaddax.z $ACC,%2,%2x\n\tvmaddy.z %4,%3,%2y"
            : "=&j"(x), "=&j"(y), "=&j"(z), "=&j"(one), "=&j"(r)
            : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
struct VU_FLOAT { qword q; };
static __inline__ struct VU_FLOAT VuFloat(float f) { struct VU_FLOAT s; __asm__("qmtc2.ni %1,%0" : "=j"(s.q) : "r"(f)); return s; }
static __inline__ qword Normalize(qword v, qword lenv, float len)
{
    qword r;
    if (len < 0.0001f)
        r = D_002A2DD0;
    else
        __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(lenv), "j"(v));
    return r;
}

static __inline__ int Moved(qword a, qword b) { return D_002BE6B0 < Length(Sub(a, b)); }

void func_00178EE0(struct P *p)
{
    func_001789F8(p);
    if (p->mode < 2) {
        U scale;
        struct VEC position;
        qword delta;
        float factor, x;
        struct CHOICE *choice;
        position = func_001A62E8(p->actor);
        delta = Reject(Sub(p->target, position.q), D_002A2DC0);
        {
            float d = X(Sqrt(LenSqXY(delta)));
            x = D_002BE6A0.a + d * (D_002BE6A0.b + d * D_002BE6A0.c);
        }
        if (x < D_002BBB60.low)
            factor = D_002BBB60.low;
        else if (D_002BBB60.high < x)
            factor = D_002BBB60.high;
        else
            factor = x;
        choice = p->driver->choice;
        switch (choice->kind) {
        case 0:
            func_00131A00(choice->control, p->rate * factor);
            { qword b; __asm__("qmfc2.ni %0,%1" : "=r"(b) : "j"(delta)); func_00209818(p->actor->control, func_002458F0(GetY(b), GetX(b))); }
            break;
        case 3: {
            qword projected = Project(func_001A6318(p->actor), delta);
            qword squared = Dot(projected, projected);
            float strength = p->rate * factor;
            qword speed = Sqrt(LenSqXY(choice->model->velocity));
            qword len = Sqrt(squared);
            strength *= X(speed);
            {
                float l = X(len);
                qword sq;
                __asm__("qmtc2.ni %1,%0" : "=j"(sq) : "r"(strength));
                scale.q = sq;
                func_0020CB28(choice->control, ScaleX(Normalize(projected, len, l), scale.q));
            }
            func_00131A00(choice->control->animation, factor);
            break;
        }
        }
        if (Moved(position.q, p->cached)) {
            p->cached = position.q;
            p->timeout = D_002BE694;
        } else {
            p->timeout -= D_002DDED0.dt;
        }
    }
}
