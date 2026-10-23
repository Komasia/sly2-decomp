typedef int qword __attribute__((mode(TI)));
struct VECTOR;
extern "C" VECTOR *func_002564C0(VECTOR *);
extern "C" qword *func_002564A8(qword *p, qword v);
extern "C" void func_001193C0(qword *p, qword n, float d);
struct VECTOR { qword q; VECTOR() { (void)func_002564C0(this); } };
struct MAT { qword r[4]; };
static inline qword MulRow(qword a0, qword a1, qword a2, qword r)
{
    qword m;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m) : "j"(a0), "j"(a1), "j"(a2), "j"(r));
    return m;
}
static inline qword Scalar(float g)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    return s;
}
static inline qword MulAdd(qword a, qword b, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s));
    return r;
}
static inline int Dot(qword a, qword b)
{
    qword p, one;
    int g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w" : "=j"(p), "=j"(one) : "j"(a), "j"(b));
    __asm__("vadday.x $ACC, %1, %1y\n\tvmaddz.x %0, %2, %1z" : "=j"(p) : "j"(p), "j"(one));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(p));
    return g;
}
extern "C" qword func_001193D8(MAT *pm, qword plane)
{
    union { qword q; float f[4]; } u;
    VECTOR v;
    v.q = plane;
    qword n = MulRow(pm->r[0], pm->r[1], pm->r[2], v.q);
    qword t = pm->r[3];
    func_002564A8(&u.q, plane);
    qword s = Scalar(u.f[3]);
    u.q = s;
    qword pos = MulAdd(t, n, s);
    int bits = Dot(pos, n);
    func_001193C0(&u.q, n, *(float *)&bits);
    return u.q;
}
