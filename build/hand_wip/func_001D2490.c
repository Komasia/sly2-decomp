typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z; } __attribute__((aligned(16))) VECTOR;
typedef union { qword q; float f; } U;
typedef struct {
    char pad0[0x51C];
    float x51C;
    char pad520[0x544 - 0x520];
    float x544;
    char pad548[0x550 - 0x548];
    float x550;
    char pad554[0x5AC - 0x554];
    void *x5AC;
    float x5B0;
} OBJ;
extern float D_002C20D0[3];
extern float D_002C20E0[2];
qword func_001A62E8(void *);
void func_001E7380(void *, qword, int, qword *, qword *, float, int, float *);
float func_002458F0(float, float);
static inline float GetX(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Dist2D(qword a, qword b)
{
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline float Clamp(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (hi < x) return hi;
    return x;
}
static inline qword AddScaled(qword a, qword b, float f)
{
    U u;
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(f));
    __asm__("vadda.xyzw $ACC, %2, $vf0\n\tvmaddx.xyzw %0, %3, %1x" : "=j"(v) : "j"(u.q), "j"(a), "j"(b));
    return v;
}
void func_001D2490(OBJ *p)
{
    VECTOR va, vb;
    qword pos, d, v, w, t, dir;
    float f, len;
    pos = func_001A62E8(p);
    func_001E7380(p->x5AC, pos, 0, (qword *)&va, (qword *)&vb, p->x5B0, 0, &p->x5B0);
    {
        float dist = Dist2D(pos, *(qword *)&va);
        f = Clamp(D_002C20D0[0] + dist * (D_002C20D0[1] + dist * D_002C20D0[2]), D_002C20E0[0], D_002C20E0[1]);
    }
    v = AddScaled(*(qword *)&va, *(qword *)&vb, f);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(w) : "j"(v), "j"(pos));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(t) : "j"(w));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(len) : "j"(d));
    if (len < 0.0001f) {
        dir = *(qword *)&vb;
    } else {
        __asm__ __volatile__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(d), "j"(w));
    }
    p->x544 = func_002458F0(GetY(dir), GetX(dir));
    p->x550 = p->x51C * 0.75f;
}
