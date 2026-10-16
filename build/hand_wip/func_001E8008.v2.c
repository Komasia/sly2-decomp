/* WIP (Claude agent) 12/110, plain C (no asm except sqrt.s): logic equal; left: upper/lower get f3/f0 instead of f0/f1 and their stack stores are scheduled after the 11D448 arg setup. */
struct P { char pad[0xE4]; int fE4; };
extern int D_002C3650;
float func_001E6648(struct P *);
float func_0011D448(float, float);
float func_001E66C8(struct P *, float);
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float GClamp(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (hi < x) return hi;
    return x;
}
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
float func_001E8008(struct P *p, float a, float b)
{
    float r[2];
    float t, u, v, upper, lower;
    if (p->fE4) {
        lower = a - b;
        upper = a + b;
    } else {
        float m = func_001E6648(p);
        float c = GClamp(a, b, m - b);
        lower = GMax(c - b, 0.0f);
        upper = GMin(c + b, m);
    }
    r[1] = upper;
    r[0] = lower;
    t = func_0011D448(-1.0f, 1.0f);
    switch (D_002C3650) {
    case 0:
        break;
    case 1:
        t = t * __builtin_fabsf(t);
        break;
    case 2:
        if (0.0f < t) v = t * t * (3.0f - (t + t));
        else v = t * t * (-3.0f - (t + t));
        t = v;
        break;
    case 3:
        if (0.0f < t) v = sqrtf_(t);
        else v = -sqrtf_(-t);
        t = v;
        break;
    }
    t = t * 0.5f + 0.5f;
    u = (1.0f - t) * r[0] + t * r[1];
    if (p->fE4)
        u = func_001E66C8(p, u);
    return u;
}
