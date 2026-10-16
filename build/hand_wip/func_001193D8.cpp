// wip (Claude agent): structure/frame/slots match; 23 diffs = VF register allocation only (target r1 vf4,r2 vf1,r0 vf3,v vf2; s vf1,t vf2,one vf4).
typedef int qword __attribute__((mode(TI)));
struct VECTOR;
extern "C" VECTOR *func_002564C0(VECTOR *);
extern "C" qword *func_002564A8(qword *p, qword v);
extern "C" void func_001193C0(qword *p, qword n, float d);
struct VECTOR { qword q; VECTOR() { (void)func_002564C0(this); } };
struct MAT { qword r[4]; };

extern "C" qword func_001193D8(MAT *pm, qword plane)
{
    union { qword q; float f[4]; } u;
    qword n, t;
    VECTOR v;
    v.q = plane;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(n) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v.q));
    t = pm->r[3];
    func_002564A8(&u.q, plane);
    float d = u.f[3];
    qword pos, one, p2;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(d));
    u.q = s;
    __asm__("vadda.xyzw $ACC, %2, $vf0\n\tvmaddx.xyzw %0, %1, %3x" : "=j"(pos) : "j"(n), "j"(t), "j"(s));
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w" : "=j"(p2), "=j"(one) : "j"(pos), "j"(n));
    __asm__("vadday.x $ACC, %1, %1y\n\tvmaddz.x %0, %2, %1z" : "=j"(p2) : "j"(p2), "j"(one));
    int bits;
    __asm__("qmfc2.ni %0, %1" : "=r"(bits) : "j"(p2));
    func_001193C0(&u.q, n, *(float *)&bits);
    return u.q;
}
