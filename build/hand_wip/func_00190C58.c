typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct T { char pad[0x70]; qword x70; };
struct S { char pad[0x134]; int x134; };
struct P { char pad[0x18C4]; struct S *x18c4; char pad2[0x19CC-0x18C8]; struct T *x19cc; };
extern qword D_002A2DC0;
qword func_001A62E8(void *p);
qword func_00190C58(struct P *p)
{
    qword q, d, l, t, dir, r;
    U s;
    float g;
    q = func_001A62E8(p->x18c4);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(q), "j"(p->x19cc->x70));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q"
            : "=&j"(l), "=&j"(t) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    if (g < 0.0001f)
        dir = D_002A2DC0;
    else
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(l), "j"(d));
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(p->x18c4->x134));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(q), "j"(dir), "j"(s.q));
    return r;
}
