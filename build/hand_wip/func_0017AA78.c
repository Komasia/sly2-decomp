typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float g[4];} U;
struct P{char pad0[0x10];void*actor;char pad14[0x5C-0x14];void*target;};
struct REQUEST{int flag;float along,up;int padC;qword point,direction;};
extern qword D_002A2DC0,D_002A2DA0;
extern float D_002BE6C4;
qword func_001A62E8(void*);
static inline qword ToVU(qword word){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(word));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Reject(qword a,qword n){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a),"j"(n));__asm__("vmulx.xyzw %0,%1,%2x":"=j"(d):"j"(n),"j"(d));return Sub(a,d);}
static inline qword Normal(qword a,qword fallback){register qword d __asm__("vf1");qword one;float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));if(len<0.0001f){d=fallback;}else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(d):"j"(d),"j"(a));}return d;}

static inline qword Scalar(unsigned int word){U u;__asm__("qmtc2.ni %1,%0":"=j"(u.q):"r"(word));return u.q;}
static inline qword MAdd2(qword p,qword a,unsigned int sa,qword b,unsigned int sb){qword qa=Scalar(sa),qb=Scalar(sb);__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"+j"(p):"j"(a),"j"(qa),"j"(b),"j"(qb));return p;}
static inline qword MAdd(qword p,qword b,unsigned int word){qword q=Scalar(word);__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(b),"j"(q));return p;}
void func_0017AA78(struct P*p,struct REQUEST*request,qword*outPoint,qword*outDirection){

 qword first=ToVU(func_001A62E8(p->actor));
 qword direction=Normal(Reject(Sub(first,func_001A62E8(p->target)),D_002A2DC0),D_002A2DA0);
 register qword*address __asm__("$2")=&D_002A2DC0;qword up;__asm__("lqc2 %0,%1":"=j"(up):"m"(*address));
 *outPoint=MAdd2(request->point,direction,*(unsigned int*)&request->along,up,*(unsigned int*)&request->up);
 *outDirection=MAdd(request->direction,up,*(unsigned int*)&D_002BE6C4);
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char REQUEST_Size[(sizeof(struct REQUEST)==48)?1:-1];
typedef char P_actor_Offset[((unsigned)&((struct P*)0)->actor==0x10)?1:-1];
typedef char P_target_Offset[((unsigned)&((struct P*)0)->target==0x5C)?1:-1];
typedef char REQUEST_flag_Offset[((unsigned)&((struct REQUEST*)0)->flag==0)?1:-1];
typedef char REQUEST_along_Offset[((unsigned)&((struct REQUEST*)0)->along==4)?1:-1];
typedef char REQUEST_up_Offset[((unsigned)&((struct REQUEST*)0)->up==8)?1:-1];
typedef char REQUEST_point_Offset[((unsigned)&((struct REQUEST*)0)->point==0x10)?1:-1];
typedef char REQUEST_direction_Offset[((unsigned)&((struct REQUEST*)0)->direction==0x20)?1:-1];
