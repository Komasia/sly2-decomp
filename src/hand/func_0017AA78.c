/* JOBB1::GetTarget: where a launched guard flies: the owner's launch target's place, pushed out by its radius along
 * the guard's flat direction from the owner (x when they coincide) and raised by its dz; the velocity: the target's,
 * with a downward pull (D_002BE6C4 along z). SafeHouse port (aihit.cpp JOBB1::GetTarget). Hand-scheduled VU code. */
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float g[4];} U;
struct JOBB1{char pad0[0x10];void*pguard;char pad14[0x5C-0x14];void*ploOwner;};
struct LAUNCHTARGET{int fActive;float sRadius,dz;int padC;qword pos,vel;};
extern qword g_normalZ,D_002A2DA0;
extern float D_002BE6C4;
qword PosOfLo__FP2LO(void*);
static inline qword ToVU(qword word){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(word));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Reject(qword a,qword n){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a),"j"(n));__asm__("vmulx.xyzw %0,%1,%2x":"=j"(d):"j"(n),"j"(d));return Sub(a,d);}
static inline qword Normal(qword a,qword fallback){register qword d __asm__("vf1");qword one;float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));if(len<0.0001f){d=fallback;}else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(d):"j"(d),"j"(a));}return d;}

static inline qword NativePoint(qword pos,qword vel,qword sRadius,qword dz,qword height,unsigned int*high){register unsigned int h __asm__("$2");__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x\n\tlui %1,%%hi(%6)":"+j"(pos),"=r"(h):"j"(vel),"j"(sRadius),"j"(dz),"j"(height),"i"(&D_002BE6C4));*high=h;return pos;}
static inline qword NativeHeading(qword pos,qword dz,qword height){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(pos):"j"(dz),"j"(height));return pos;}
static inline void PublishPoint(U*home,qword scalar,qword*out,qword pos){__asm__ volatile("sqc2 %2,%0\n\tsqc2 %3,%1":"=m"(home->q),"=m"(*out):"j"(scalar),"j"(pos));}
// name: SafeHouse port (JOBB1::GetTarget)
void GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(struct JOBB1*p,struct LAUNCHTARGET*ptarget,qword*ppos,qword*pvel){

 qword first=ToVU(PosOfLo__FP2LO(p->pguard));
 qword vel=Normal(Reject(Sub(first,PosOfLo__FP2LO(p->ploOwner)),g_normalZ),D_002A2DA0);
 {U scalar;
 register unsigned int addressWord __asm__("$2")=(unsigned int)&g_normalZ;
 register qword sRadius __asm__("vf4"),dz __asm__("vf5"),pos __asm__("vf2"),height __asm__("vf6");
 __asm__("lw $3,%5\n\tlqc2 %2,0(%0)\n\tqmtc2.ni $3,%1\n\tlw %0,%6\n\tlqc2 %3,%7\n\tqmtc2.ni %0,%4":"+&r"(addressWord),"=j"(sRadius),"=j"(dz),"=j"(pos),"=j"(height):"m"(ptarget->sRadius),"m"(ptarget->dz),"m"(ptarget->pos):"$3","memory");
 {unsigned int high;
 qword result=NativePoint(pos,vel,sRadius,dz,height,&high);
 register unsigned int constantWord __asm__("$2")=high;
 register qword heading __asm__("vf1"),constant __asm__("vf3");
 __asm__("lqc2 %1,%3\n\tlw %0,%%lo(%4)(%0)\n\tqmtc2.ni %0,%2":"+r"(constantWord),"=j"(heading),"=j"(constant):"m"(ptarget->vel),"i"(&D_002BE6C4):"memory");
 PublishPoint(&scalar,sRadius,ppos,result);
 heading=NativeHeading(heading,dz,constant);
 PublishPoint(&scalar,height,pvel,heading);
 scalar.q=constant;}}

}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char REQUEST_Size[(sizeof(struct LAUNCHTARGET)==48)?1:-1];
typedef char JOBB1_actor_Offset[((unsigned)&((struct JOBB1*)0)->pguard==0x10)?1:-1];
typedef char JOBB1_target_Offset[((unsigned)&((struct JOBB1*)0)->ploOwner==0x5C)?1:-1];
typedef char REQUEST_flag_Offset[((unsigned)&((struct LAUNCHTARGET*)0)->fActive==0)?1:-1];
typedef char REQUEST_along_Offset[((unsigned)&((struct LAUNCHTARGET*)0)->sRadius==4)?1:-1];
typedef char REQUEST_up_Offset[((unsigned)&((struct LAUNCHTARGET*)0)->dz==8)?1:-1];
typedef char REQUEST_point_Offset[((unsigned)&((struct LAUNCHTARGET*)0)->pos==0x10)?1:-1];
typedef char REQUEST_direction_Offset[((unsigned)&((struct LAUNCHTARGET*)0)->vel==0x20)?1:-1];

typedef char pointer_Width[sizeof(void*)==4?1:-1];
typedef char word_Width[sizeof(unsigned int)==4?1:-1];
typedef char integer_Width[sizeof(int)==4?1:-1];
typedef char float_Width[sizeof(float)==4?1:-1];
typedef char qword_Alignment[__alignof__(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char JOBB1_PrefixSize[sizeof(struct JOBB1)==0x60?1:-1];
typedef char JOBB1_Alignment[__alignof__(struct JOBB1)==4?1:-1];
typedef char REQUEST_Alignment[__alignof__(struct LAUNCHTARGET)==16?1:-1];
typedef char U_q_Offset[(unsigned)&((U*)0)->q==0?1:-1];
typedef char U_scalar_Offset[(unsigned)&((U*)0)->g==0?1:-1];
