/* JOBB2::Choose: at most every D_002BE710 range s (random): from the guard's first list (option 426: the objects it
 * attacks, +0xF98) the in-world object at the lowest cost - its distance, through D_002BE720's quadratic for the
 * previous choice, plus D_002BE730's quadratic (clamped to D_002BE740) of the distance of each second-list object
 * (+0xFAC) lying along the way; then the nearest second-list object within 800 that lies along the way to that one
 * (within 500 of the segment) is preferred as the selection. SafeHouse port (aipursuit.cpp JOBB2::Choose).
 * Hand-scheduled asm pins the matched register use. */
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct RANGE{float lo,hi;};
struct POLY{float a,b,c;};
struct GUARD{char pad[0x28];unsigned long grf;char pad30[0xF94-0x30];int cChoice;GUARD*aploChoice[4];GUARD*Choice(int i){return aploChoice[i];}int cNear;GUARD*aploNear[0];};
struct JOBB2{char pad[0x10];GUARD*pguard;char pad14[0x38-0x14];GUARD*ploPreferred;GUARD*ploNear;GUARD*ploSelected;float tChoose;};
struct WORK{float t,d,t2,d2;U origin,bestPoint;};
#include "clock.h"
extern "C"{
 extern RANGE D_002BE740;
 extern POLY D_002BE720,D_002BE730;
 float GRandInRange(float,float) asm("GRandInRange__Fff");
 qword PosOfLo(GUARD*) asm("PosOfLo__FP2LO");
 void ParamSegPoint(qword,qword,qword,qword*,float*,float*) asm("ParamSegPoint__FG9VU_VECTORN20P6VECTORN23");
}
static inline unsigned long Eligible(unsigned long grf){return (grf>>60)&1;}
static inline qword From(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Load(U*u){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(u->q));return r;}
static inline float X(qword q){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline float Length(qword v){register qword one __asm__("vf2"); qword d=v;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d),"=&j"(one):"j"(v));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return X(d);
}
static inline float Distance(U*origin,qword point){register qword a __asm__("vf2")=origin->q;qword b=point,d;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));return Length(d);}
static inline float DistanceFrom(qword point,U*origin){qword a=point,b=Load(origin),d;__asm__("vsub.xyzw %0,%1,%2":"=&j"(d):"j"(a),"j"(b));return Length(d);}
static inline qword To(qword a){return a;}
static inline void Store(U*u,qword a){__asm__("sqc2 %1,%0":"=m"(u->q):"j"(a));}
static inline void ClampIn(float*x,RANGE*p){float lo=p->lo,hi=p->hi;if(*x<lo)*x=lo;else if(hi<*x)*x=hi;}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char POLY_Size[sizeof(POLY)==12?1:-1];
typedef char RANGE_Size[sizeof(RANGE)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==48?1:-1];
typedef char GUARD_flags_Offset[FIELD_OFFSET(GUARD,grf)==40?1:-1];
typedef char GUARD_count_Offset[FIELD_OFFSET(GUARD,cChoice)==3988?1:-1];
typedef char GUARD_choices_Offset[FIELD_OFFSET(GUARD,aploChoice)==3992?1:-1];
typedef char GUARD_nearCount_Offset[FIELD_OFFSET(GUARD,cNear)==4008?1:-1];
typedef char GUARD_aploNear_Offset[FIELD_OFFSET(GUARD,aploNear)==4012?1:-1];
typedef char JOBB2_actor_Offset[FIELD_OFFSET(JOBB2,pguard)==16?1:-1];
typedef char JOBB2_preferred_Offset[FIELD_OFFSET(JOBB2,ploPreferred)==56?1:-1];
typedef char JOBB2_ploNear_Offset[FIELD_OFFSET(JOBB2,ploNear)==60?1:-1];
typedef char JOBB2_selected_Offset[FIELD_OFFSET(JOBB2,ploSelected)==64?1:-1];
typedef char JOBB2_time_Offset[FIELD_OFFSET(JOBB2,tChoose)==68?1:-1];
typedef char WORK_t_Offset[FIELD_OFFSET(WORK,t)==0?1:-1];
typedef char WORK_d_Offset[FIELD_OFFSET(WORK,d)==4?1:-1];
typedef char WORK_t2_Offset[FIELD_OFFSET(WORK,t2)==8?1:-1];
typedef char WORK_d2_Offset[FIELD_OFFSET(WORK,d2)==12?1:-1];
typedef char WORK_origin_Offset[FIELD_OFFSET(WORK,origin)==16?1:-1];
typedef char WORK_bestPoint_Offset[FIELD_OFFSET(WORK,bestPoint)==32?1:-1];
typedef char POLY_a_Offset[FIELD_OFFSET(POLY,a)==0?1:-1];
typedef char POLY_b_Offset[FIELD_OFFSET(POLY,b)==4?1:-1];
typedef char POLY_c_Offset[FIELD_OFFSET(POLY,c)==8?1:-1];
typedef char RANGE_lo_Offset[FIELD_OFFSET(RANGE,lo)==0?1:-1];
typedef char RANGE_hi_Offset[FIELD_OFFSET(RANGE,hi)==4?1:-1];
// name: SafeHouse port (JOBB2::Choose)
extern "C" void Choose__5JOBB2(JOBB2*p){
 WORK work;
 GUARD*best;
 float lower;
 qword zero;
 float now=g_clock.t;
 if(now<p->tChoose)return;
 // D_002BE710 holds the random-delay range.
 register unsigned int randomAddress __asm__("$2");
 __asm__("vsub.xyzw %0,$vf0,$vf0\n\tlui %1,0x2c":"=j"(zero),"=r"(randomAddress));
 __asm__("sqc2 %4,%0\n\tdaddu %2,%z5,$zero\n\tlwc1 %1,-0x18f0(%3)\n\taddiu %3,%3,-0x18f0"
   :"=m"(work.bestPoint.q),"=f"(lower),"=&r"(best),"+r"(randomAddress)
   :"j"(zero),"J"(0),"m"(*(float*)(randomAddress-0x18f0)));
 p->tChoose=now+GRandInRange(lower,((RANGE*)randomAddress)->hi);
 work.origin.q=PosOfLo(p->pguard);
 // D_002A55FC supplies the initial selection cost.
 int i;GUARD*pguard;unsigned int limitHigh;
 {register int firstIndex __asm__("$5");register GUARD*firstActor __asm__("$4");register unsigned int high __asm__("$3");
  __asm__("lui %0,0x2a\n\tdaddu %1,$zero,$zero\n\tlw %2,%3"
    :"=&r"(high),"=&r"(firstIndex),"=r"(firstActor):"m"(p->pguard));
  limitHigh=high;i=firstIndex;pguard=firstActor;
 }
 float bestCost=*(float*)(limitHigh+0x55fc);
 if(pguard->cChoice>0)do{
  GUARD*choice=pguard->Choice(i);
  if(Eligible(choice->grf)){
  qword candidate=From(PosOfLo(choice));
  float cost=Distance(&work.origin,candidate);
  if(choice==p->ploPreferred)cost=D_002BE720.a+cost*(D_002BE720.b+cost*D_002BE720.c);
  for(int j=0;j<p->pguard->cNear;j++){
   qword position=PosOfLo(p->pguard->aploNear[j]);
   ParamSegPoint(position,work.origin.q,To(candidate),0,&work.t,&work.d);
   if(work.t<0.0f)continue;
   if(work.t>1.0f)continue;
   float penalty=D_002BE730.a+work.d*(D_002BE730.b+work.d*D_002BE730.c);
   ClampIn(&penalty,&D_002BE740);cost+=penalty;
  }
  if(cost<bestCost){Store(&work.bestPoint,candidate);bestCost=cost;best=choice;}
  }
  ++i;pguard=p->pguard;
 }while(i<pguard->cChoice);
 p->ploPreferred=best;
 GUARD*nearest=0;float distance=800.0f;
 for(int k=0;k<p->pguard->cNear;k++){
  GUARD*choice=p->pguard->aploNear[k];
  qword position=From(PosOfLo(choice));
  float f=DistanceFrom(position,&work.origin);
  if(f>distance)continue;
  if(best){
   ParamSegPoint(To(position),work.origin.q,work.bestPoint.q,0,&work.t2,&work.d2);
   if(work.t2<0.0f)continue;
   if(work.t2>1.0f)continue;
   if(work.d2>500.0f)continue;
  }
  nearest=choice;distance=f;
 }
 p->ploNear=nearest;p->ploSelected=nearest?nearest:p->ploPreferred;
}

typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Int_Size[sizeof(int)==4?1:-1];
typedef char UInt_Size[sizeof(unsigned int)==4?1:-1];
typedef char Float_Size[sizeof(float)==4?1:-1];
typedef char Long_Size[sizeof(unsigned long)==8?1:-1];
typedef char Qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char WORK_Alignment[__alignof__(WORK)==16?1:-1];
typedef char GUARD_View_Size[sizeof(GUARD)==0xfb0?1:-1];
typedef char GUARD_Alignment[__alignof__(GUARD)==8?1:-1];
typedef char JOBB2_Size[sizeof(JOBB2)==0x48?1:-1];
