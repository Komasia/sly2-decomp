typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DC0;
extern qword D_002A2DA0;
extern float D_002BE6C4;
struct S { char pad[0x10]; void *p10; char pad2[0x5C - 0x14]; void *p5C; };
struct T { int n0; float f4; float f8; int nC; qword v10; qword v20; };
qword func_001A62E8(void *p);
static __inline__ qword MAdd(qword p, qword up, int s) {
    U u;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(s));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(up), "j"(u.q));
    return r;
}
static __inline__ qword VF(int s) {
    U u;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(s));
    return u.q;
}
static __inline__ qword MAdd2(qword p, qword a, int sa, qword b, int sb) {
    qword r;
    qword qa = VF(sa);
    qword qb = VF(sb);
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
            : "=j"(r) : "j"(p), "j"(a), "j"(qa), "j"(b), "j"(qb));
    return r;
}
void func_0017AA78(struct S *p, struct T *t, qword *pa, qword *pb)
{
    qword a, b;
    qword d, dot, one, proj, len, dir;
    float f;
    __asm__("qmtc2.ni %1, %0" : "=j"(a) : "r"(func_001A62E8(p->p10)));
    b = func_001A62E8(p->p5C);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(dot), "=&j"(one) : "j"(d), "j"(D_002A2DC0));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(proj) : "j"(D_002A2DC0), "j"(dot));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(d), "j"(proj));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(len), "=&j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(len));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(len));
    dir = D_002A2DA0;
    if (!(f < 1e-4f))
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(len), "j"(d));
    {
    qword up = D_002A2DC0;
    *pa = MAdd2(t->v10, dir, *(int *)&t->f4, up, *(int *)&t->f8);
    *pb = MAdd(t->v20, up, *(int *)&D_002BE6C4);
    }
}
