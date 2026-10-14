typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct S { char pad[0x40]; qword row[3]; };
extern qword D_002A2DB0;
static inline qword ReadRow(const qword *base,int offset) {qword r;__asm__("lqc2 %0,%2(%1)":"=j"(r):"r"(base),"i"(offset),"m"(base[offset/16]));return r;}
static inline qword Rot(struct S *p,qword v) {
    qword r=p->row[0],one,a,b,c;
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y" : "+j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(ReadRow(p->row,16)), "j"(ReadRow(p->row,32)), "j"(v));
    return r;
}
static inline qword Norm(qword v,qword fallback) {
    register qword d __asm__("vf1");register qword one __asm__("vf2");qword r;float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(d));
    if(f<0.0001f)__asm__("qmtc2.ni %1,%0":"=j"(d):"r"(fallback));
    else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(d):"j"(v));
    __asm__("qmfc2.ni %0,%1":"=r"(r):"j"(d));return r;
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

typedef char transformed_direction_layout[(sizeof(qword)==16 && sizeof(union U)==16 && sizeof(void*)==4 && (unsigned)&((struct S*)0)->row==0x40 && sizeof(((struct S*)0)->row)==0x30 && sizeof(((struct S*)0)->row[0])==0x10)?1:-1];
