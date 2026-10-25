typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct VTE { short delta, pad; void *fn; };
struct SO { char pad0[0xC]; VTE *vt; char pad10[0x60]; qword position; };
struct OWNER { char pad0[0x150]; SO *source; void *factory; SO *first; };
struct LM { float gMin, gMax; };
struct GAME { int dummy; };
extern "C" {
extern GAME D_003DD490;
extern qword D_002A2DC0, D_002A2DA0, D_002C0D60;
extern LM D_002C0CF0, D_002C0CF8, D_002C0CE0;
extern float D_002C0CE8, D_002C0CEC, D_002A76E8;
void *func_001C4840(GAME *);
qword func_001A62E8(void *);
float func_0011D448(float, float);
qword func_0011E1A0(float, float, float);
M3 func_0011B830(qword, qword);
qword func_001D69F0(qword, qword, qword, float);
int func_00132B10(SO *, int);
void func_001C6BD0(SO *, qword, qword, float, float);
SO *func_001CB250(void *, int);
void func_001C2DB8(OWNER *);
}

static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Scale(qword v, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(len) : "j"(d));
    return len;
}
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
static inline qword Transform(const M3 &m, qword q)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(q));
    return r;
}
static inline float Rand(const LM &lm) { return func_0011D448(lm.gMin, lm.gMax); }
static inline void SetState(SO *p, int state) { VTE *v = p->vt; ((void (*)(void *, int))v[76].fn)((char *)p + v[76].delta, state); }
static inline void Reset(SO *p) { VTE *v = p->vt; ((void (*)(void *))v[8].fn)((char *)p + v[8].delta); }
static inline void SetParent(SO *p, SO *parent) { VTE *v = p->vt; ((void (*)(void *, SO *))v[39].fn)((char *)p + v[39].delta, parent); }
static inline void SetVelocity(SO *p, qword velocity) { VTE *v = p->vt; ((void (*)(void *, qword))v[35].fn)((char *)p + v[35].delta, velocity); }

extern "C" SO *func_001C2EF0(OWNER *p, int count)
{
    SO *first = 0;
    for (int i = 0; i < count; i++) {
        SO *node;
        if (i == 0)
            node = p->first;
        else {
            node = func_001CB250(p->factory, 0);
            if (node && func_00132B10(node, 0x5A))
                SetState(node, 2);
        }
        if (!node)
            break;
        if (!first)
            first = node;
        qword start = p->source->position;
        qword target = func_001A62E8(func_001C4840(&D_003DD490));
        float pan = Rand(D_002C0CF0);
        qword offset = func_0011E1A0(pan, Rand(D_002C0CF8), -75.0f);
        qword delta = Sub(target, start);
        qword side = Sub(delta, Scale(D_002A2DC0, Dot(delta, D_002A2DC0)));
        M3 mat;
        mat = func_0011B830(Normalize(side, D_002A2DA0), D_002A2DC0);
        qword dest = Add(target, Transform(mat, offset));
        qword velocity = func_001D69F0(start, dest, D_002C0D60, Rand(D_002C0CE0));
        if (func_00132B10(node, 0x5A)) {
            float lifetime;
            if (func_00132B10(node, 0x5B) || func_00132B10(node, 0x5D))
                lifetime = (float)i * D_002C0CEC;
            else
                lifetime = D_002A76E8;
            func_001C6BD0(node, p->source->position, velocity, (float)i * D_002C0CE8, lifetime);
        } else {
            Reset(node);
            SetParent(node, p->source);
            SetVelocity(node, velocity);
        }
    }
    func_001C2DB8(p);
    return first;
}
