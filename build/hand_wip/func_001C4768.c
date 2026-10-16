typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct S { char pad[0x40]; qword row[3]; };
extern qword D_002A2DB0;
static inline const qword* RowBase(const struct S*p){register const qword*result __asm__("$3");__asm__("addiu %0,%1,64":"=r"(result):"r"(p));return result;}
static inline int FallbackPage(void){register int result __asm__("$2");__asm__("lui %0,%%hi(%1)":"=r"(result):"i"(&D_002A2DB0));return result;}
static inline const qword* ThirdAndAddress(const qword*base,int page,qword*third){register qword row __asm__("vf3");register const qword*address __asm__("$2");__asm__("lqc2 %0,32(%2)\n\taddiu %1,%3,%%lo(%4)":"=j"(row),"=r"(address):"r"(base),"r"(page),"i"(&D_002A2DB0),"m"(base[2]));*third=row;return address;}
static inline qword FirstRow(const struct S*p){return p->row[0];}
static inline qword SecondRow(const qword*base){register qword row __asm__("vf1");__asm__("lqc2 %0,16(%1)":"=j"(row):"r"(base),"m"(base[1]));return row;}
static inline qword Rot(struct S *p,const qword*base,qword v,qword third) {
    register qword second __asm__("vf1")=SecondRow(base),r __asm__("vf2")=FirstRow(p),one __asm__("vf7"),a __asm__("vf6"),b __asm__("vf5"),c __asm__("vf4");
    register qword vector __asm__("vf8")=v;
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y" : "+j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(second), "j"(third), "j"(vector));
    return r;
}
static inline qword Norm(qword v,qword fallback) {
    register qword d __asm__("vf1");register qword one __asm__("vf2");qword r;float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(d));
    if(f<0.0001f)d=fallback;
    else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(d):"j"(v));
    __asm__("qmfc2.ni %0,%1":"=r"(r):"j"(d));return r;
}
qword func_001C4768(struct S *p,qword dir) {
    union U v;
    const qword*rows=RowBase(p);
    int page=FallbackPage();
    qword third;
    const qword*address=ThirdAndAddress(rows,page,&third);
    qword fallback=*address;
    v.q=Rot(p,rows,dir,third);
    v.f[0]=-v.f[1];
    v.f[1]=v.f[2];
    v.f[2]=0.0f;
    return Norm(v.q,fallback);
}

typedef char transformed_direction_layout[(sizeof(qword)==16 && sizeof(union U)==16 && sizeof(void*)==4 && (unsigned)&((struct S*)0)->row==0x40 && sizeof(((struct S*)0)->row)==0x30 && sizeof(((struct S*)0)->row[0])==0x10 && sizeof(float)==4 && __alignof__(qword)==16 && (unsigned)&((struct S*)0)->row[1]==0x50 && (unsigned)&((struct S*)0)->row[2]==0x60 && (unsigned)&((union U*)0)->f[1]==4 && (unsigned)&((union U*)0)->f[2]==8 && (unsigned)&((union U*)0)->f[3]==12)?1:-1];
