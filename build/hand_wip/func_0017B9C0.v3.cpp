// v3 (Claude agent): aligned 10->2: X() qmfc2 straight to a float, Distance vsub without early-clobber and origin pinned to vf2. Left: lui before the Clear sqc2, addu operand order in Choice.
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct RANGE{float lo,hi;};
struct POLY{float a,b,c;};
struct P{char pad[0x28];unsigned long flags;char pad30[0xF94-0x30];int count;char choices[16];P*Choice(int i){return *(P**)((char*)this+0xF98+4*i);}int nearCount;P*near[0];};
struct C{char pad[0x10];P*actor;char pad14[0x38-0x14];P*preferred;P*near;P*selected;float time;};
struct WORK{float t,d,t2,d2;U origin,bestPoint;};
struct CLOCK{float time,dt;};
extern "C"{
 extern CLOCK D_002DDED0;
 extern RANGE D_002BE710,D_002BE740;
 extern POLY D_002BE720,D_002BE730;
 extern float D_002A55FC;
 float func_0011D448(float,float);
 qword func_001A62E8(P*);
 void func_0011ED40(qword,qword,qword,qword*,float*,float*);
}
static inline unsigned long Eligible(unsigned long flags){return (flags>>60)&1;}
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
static inline void Clear(U*u){qword q;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(q));__asm__ __volatile__("sqc2 %1,%0":"=m"(u->q):"j"(q));}
static inline void ClampIn(float*x,RANGE*p){float lo=p->lo,hi=p->hi;if(*x<lo)*x=lo;else if(hi<*x)*x=hi;}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char POLY_Size[sizeof(POLY)==12?1:-1];
typedef char RANGE_Size[sizeof(RANGE)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==48?1:-1];
typedef char P_flags_Offset[FIELD_OFFSET(P,flags)==40?1:-1];
typedef char P_count_Offset[FIELD_OFFSET(P,count)==3988?1:-1];
typedef char P_choices_Offset[FIELD_OFFSET(P,choices)==3992?1:-1];
typedef char P_nearCount_Offset[FIELD_OFFSET(P,nearCount)==4008?1:-1];
typedef char P_near_Offset[FIELD_OFFSET(P,near)==4012?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==16?1:-1];
typedef char C_preferred_Offset[FIELD_OFFSET(C,preferred)==56?1:-1];
typedef char C_near_Offset[FIELD_OFFSET(C,near)==60?1:-1];
typedef char C_selected_Offset[FIELD_OFFSET(C,selected)==64?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(C,time)==68?1:-1];
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
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_0017B9C0(C*p){
 WORK work;
 float now=D_002DDED0.time;
 if(now<p->time)return;
 Clear(&work.bestPoint);
 P*best=0;
 p->time=now+func_0011D448(D_002BE710.lo,D_002BE710.hi);
 work.origin.q=func_001A62E8(p->actor);
 float bestCost=D_002A55FC;
 for(int i=0;i<p->actor->count;i++){
  P*choice=p->actor->Choice(i);
  if(!Eligible(choice->flags))continue;
  qword candidate=From(func_001A62E8(choice));
  float cost=Distance(&work.origin,candidate);
  if(choice==p->preferred)cost=D_002BE720.a+cost*(D_002BE720.b+cost*D_002BE720.c);
  for(int j=0;j<p->actor->nearCount;j++){
   qword position=func_001A62E8(p->actor->near[j]);
   func_0011ED40(position,work.origin.q,To(candidate),0,&work.t,&work.d);
   if(work.t<0.0f)continue;
   if(work.t>1.0f)continue;
   float penalty=D_002BE730.a+work.d*(D_002BE730.b+work.d*D_002BE730.c);
   ClampIn(&penalty,&D_002BE740);cost+=penalty;
  }
  if(cost<bestCost){Store(&work.bestPoint,candidate);bestCost=cost;best=choice;}
 }
 p->preferred=best;
 P*nearest=0;float distance=800.0f;
 for(int k=0;k<p->actor->nearCount;k++){
  P*choice=p->actor->near[k];
  qword position=From(func_001A62E8(choice));
  float f=DistanceFrom(position,&work.origin);
  if(f>distance)continue;
  if(best){
   func_0011ED40(To(position),work.origin.q,work.bestPoint.q,0,&work.t2,&work.d2);
   if(work.t2<0.0f)continue;
   if(work.t2>1.0f)continue;
   if(work.d2>500.0f)continue;
  }
  nearest=choice;distance=f;
 }
 p->near=nearest;p->selected=nearest?nearest:p->preferred;
}
