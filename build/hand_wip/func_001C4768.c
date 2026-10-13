typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct S { char pad[0x40]; qword row[3]; };
extern qword D_002A2DB0;
static inline qword Rot(struct S *p, qword v) {
    qword a,b,c,one,r;
    __asm__("vmul.xyzw %2,%5,%8\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%8\n\tvmul.xyzw %4,%7,%8\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y" : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(p->row[0]), "j"(p->row[1]), "j"(p->row[2]), "j"(v));
    return r;
}
static inline qword Norm(qword v,qword fallback) {
    qword d,one,r; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    if(f < 0.0001f) __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(fallback));
    else __asm__ volatile("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
qword func_001C4768(struct S *p,qword dir) {
    union U v;
    qword fallback=D_002A2DB0;
    v.q=Rot(p,dir);
    v.f[0]=-v.f[1];
    v.f[1]=v.f[2];
    v.f[2]=0.0f;
    return Norm(v.q,fallback);
}
