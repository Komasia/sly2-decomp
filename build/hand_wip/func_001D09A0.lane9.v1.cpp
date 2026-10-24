typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct P { char pad40[0x40]; qword row0; qword row1; qword row2; char pad70[0x20]; qword velocity; char padA0[0x24]; float drag; };
struct CLOCK { float t; float dt; };
extern CLOCK D_002DDED0;
extern float D_002C2010, D_002C2014, D_002C2018, D_002C2020, D_002C2024, D_002C2028, D_002C202C;
extern qword D_002A2DA0;
extern "C" {
M3 *func_0011B500(M3 *, float, qword);
float func_0011E290(qword, qword, qword *, qword *);
void func_001CF0A0(P *);
}
static inline qword Rotate(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return r;
}
static inline qword Dot3(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
extern "C" void func_001D09A0(P *p)
{
    M3 spin;
    U scalar;
    qword first = p->row0;
    qword dotv = Dot3(p->velocity, first);
    float dot;
    __asm__("qmfc2.ni %0,%1" : "=r"(dot) : "j"(dotv));
    float turn = D_002C2010 + dot * (D_002C2014 + dot * D_002C2018);
    if (turn < D_002C2020) turn = D_002C2020;
    else if (D_002C2024 < turn) turn = D_002C2024;
    func_0011B500(&spin, turn * D_002DDED0.dt, p->row1);
    p->velocity = Rotate(spin, p->velocity);
    float drag = p->drag;
    qword r0 = Rotate(spin, p->row0);
    qword r1 = Rotate(spin, p->row1);
    qword r2 = Rotate(spin, p->row2);
    p->row1 = r1;
    p->row2 = r2;
    p->drag = 0.0f;
    p->row0 = r0;
    qword par, perp;
    func_0011E290(p->velocity, first, &par, &perp);
    qword len = Dot3(par, par);
    float lenf;
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tqmfc2.ni %0,%1" : "=r"(lenf), "+j"(len));
    if (lenf < 0.0001f) par = D_002A2DA0;
    else { __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(par) : "j"(len), "j"(par)); }
    float target = D_002C2028;
    float along = target + (lenf - target) * (1.0f + D_002C202C * D_002DDED0.dt);
    float across = 1.0f + drag * D_002DDED0.dt;
    qword sa, sb;
    __asm__("qmtc2.ni %1,%0" : "=j"(sa) : "r"(along));
    __asm__("qmtc2.ni %1,%0" : "=j"(sb) : "r"(across));
    __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(p->velocity) : "j"(par), "j"(perp), "j"(sa), "j"(sb));
    func_001CF0A0(p);
    p->drag = drag;
}
