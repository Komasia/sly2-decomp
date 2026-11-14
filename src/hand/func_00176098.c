#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];}U;
typedef struct P P;
typedef struct OWNER{char pad[0x10];void*region;}OWNER;
typedef struct TUNE{char pad[0xDC];OWNER*owner;}TUNE;
typedef struct SCALE{char pad[0x20];float value;}SCALE;
struct P{char pad[0xE8];TUNE*tuning;char padEC[0x314-0xEC];float close,far;char pad31C[0xF40-0x31C];int emit;float time;char padF48[0xFBC-0xF48];int mode;int padFC0;SCALE*scale;};
typedef struct C{char pad[0x10];P*actor;int pad14;void*sub;char pad1C[0x30-0x1C];P*target;int state;char pad38[0x44-0x38];void*region;char pad48[8];U cached;}C;
typedef struct X{void*a,*b;char pad8[8];qword point;}X;
typedef struct WORK{X frame;U point;}WORK;
#include "clock.h"
extern float D_002BE614,D_003E1BE8;
void Update__5AIJOB(C*);
int FJobDone(C*) asm("FJobDone__FP5AIJOB");
int func_00209098(P*);
int FLost__9JOBPURSUE(C*);
int FTryAction__9JOBPURSUE(C*);
int FCanShoot__9JOBPURSUE(C*);
void SetPursueState__9JOBPURSUEi(C*,int);
qword PosOfLo__FP2LO(P*);
void*PregionAt__FG9VU_VECTORi(qword,int);
void func_002562A8(X*);
void SetGoal__7JOBGOTOP4GOAL(void*,X*);
int func_00175748(void*);
int func_0017B7F8(void*);
int func_00174FB8(void*);
void RaiseGuardAlarm__FP5GUARDP2LO(P*,P*);
static inline void StorePoint(U*home,qword a){__asm__("sq %1,%0":"=m"(home->q):"r"(a):"memory");}
static inline float XFloat(qword q){register float f __asm__("$3");__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline qword Root(qword q){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(q));return q;}
static inline float DistanceXY(C*p,U*point,qword pos,P**actor,int*mode){
 register qword a __asm__("vf2"),b __asm__("vf3"),d __asm__("vf1");P*o;register int n __asm__("$5");float f;
 b=pos;o=p->actor;a=point->q;
 *mode=o->mode;
 __asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));
 __asm__("vmul.xy %0,%0,%0":"+j"(d));__asm__("vaddy.x %0,%0,%0y":"+j"(d));d=Root(d);
 __asm__("qmfc2.ni %0,%1":"=r"(n):"j"(d));__asm__("mtc1 %1,%0":"=f"(f):"r"(n));*actor=o;return f;
}
static inline void*ActorRegion(P*actor){OWNER*owner=actor->tuning?actor->tuning->owner:0;return owner?owner->region:0;}
static inline int Moved(C*p,U*point){
 register qword a __asm__("vf2"),d __asm__("vf1");qword one;
 register char*high __asm__("$2");
 register float threshold __asm__("$f1");float distance;
 register int result __asm__("$2");
 a=point->q;
 __asm__("lui %0,%1":"=r"(high):"i"(0x2C));
 d=p->cached.q;
 __asm__("vsub.xyzw %0,%1,%0":"+j"(d):"j"(a));
 __asm__("lwc1 %2,-6636(%3)\n\tvmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d),"=&j"(one),"=f"(threshold):"r"(high),"m"(*(float*)(high-6636)));
 __asm__("addiu %1,$zero,1\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d),"=r"(result));
 distance=XFloat(d);
 result=threshold<distance?result:0;
 return result;
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char X_Size[sizeof(X)==32?1:-1];
typedef char WORK_Size[sizeof(WORK)==48?1:-1];
typedef char P_tuning_Offset[FIELD_OFFSET(P,tuning)==232?1:-1];
typedef char P_close_Offset[FIELD_OFFSET(P,close)==788?1:-1];
typedef char P_far_Offset[FIELD_OFFSET(P,far)==792?1:-1];
typedef char P_emit_Offset[FIELD_OFFSET(P,emit)==3904?1:-1];
typedef char P_time_Offset[FIELD_OFFSET(P,time)==3908?1:-1];
typedef char P_mode_Offset[FIELD_OFFSET(P,mode)==4028?1:-1];
typedef char P_scale_Offset[FIELD_OFFSET(P,scale)==4036?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==16?1:-1];
typedef char C_sub_Offset[FIELD_OFFSET(C,sub)==24?1:-1];
typedef char C_target_Offset[FIELD_OFFSET(C,target)==48?1:-1];
typedef char C_state_Offset[FIELD_OFFSET(C,state)==52?1:-1];
typedef char C_region_Offset[FIELD_OFFSET(C,region)==68?1:-1];
typedef char C_cached_Offset[FIELD_OFFSET(C,cached)==80?1:-1];
typedef char TUNE_owner_Offset[FIELD_OFFSET(TUNE,owner)==220?1:-1];
typedef char OWNER_region_Offset[FIELD_OFFSET(OWNER,region)==16?1:-1];
typedef char SCALE_value_Offset[FIELD_OFFSET(SCALE,value)==32?1:-1];
typedef char X_a_Offset[FIELD_OFFSET(X,a)==0?1:-1];
typedef char X_b_Offset[FIELD_OFFSET(X,b)==4?1:-1];
typedef char X_point_Offset[FIELD_OFFSET(X,point)==16?1:-1];
typedef char WORK_frame_Offset[FIELD_OFFSET(WORK,frame)==0?1:-1];
typedef char WORK_point_Offset[FIELD_OFFSET(WORK,point)==32?1:-1];
// name: SafeHouse port (JOBPURSUE::Update)
void Update__9JOBPURSUE(C*p){
 WORK work;int old;
 Update__5AIJOB(p);
 do{
  old=p->state;
  switch(old){
  case 0:case 3:{
   float distance;void*region;qword current;P*actor;int mode;
   if(FJobDone(p))break;
   if(func_00209098(p->actor)){SetPursueState__9JOBPURSUEi(p,5);break;}
   if(FLost__9JOBPURSUE(p)){SetPursueState__9JOBPURSUEi(p,4);break;}
   if(FTryAction__9JOBPURSUE(p)){SetPursueState__9JOBPURSUEi(p,1);break;}
   if(FCanShoot__9JOBPURSUE(p)){SetPursueState__9JOBPURSUEi(p,2);break;}
   StorePoint(&work.point,PosOfLo__FP2LO(p->target));
   current=PosOfLo__FP2LO(p->actor);
   distance=DistanceXY(p,&work.point,current,&actor,&mode);
   if(mode==8 ||mode==13){SCALE*scale=actor->scale;if(scale)distance/=scale->value;}
   region=PregionAt__FG9VU_VECTORi(work.point.q,1);
   if(p->state!=0){
    if(p->state!=3)break;
    if(distance<p->actor->close &&region==ActorRegion(p->actor)){SetPursueState__9JOBPURSUEi(p,0);break;}
    if(p->region==region&&!Moved(p,&work.point))break;
    p->region=region;p->cached=work.point;
    func_002562A8(&work.frame);
    {register qword framePoint __asm__("$3")=work.point.q;
     work.frame.point=framePoint;
    }
    SetGoal__7JOBGOTOP4GOAL(p->sub,&work.frame);
   }else{
    if(p->actor->far<distance ||region!=ActorRegion(p->actor))SetPursueState__9JOBPURSUEi(p,3);
   }
   break;
  }
  case 1:
   if(func_00209098(p->actor)){SetPursueState__9JOBPURSUEi(p,5);break;}
   if(!FJobDone(p)&&func_00175748(p->sub))SetPursueState__9JOBPURSUEi(p,0);
   break;
  case 2:
   if(func_00209098(p->actor)){SetPursueState__9JOBPURSUEi(p,5);break;}
   if(!FJobDone(p)&&func_0017B7F8(p->sub))SetPursueState__9JOBPURSUEi(p,0);
   break;
  case 4:
   if(!FJobDone(p)&&func_00174FB8(p->sub))SetPursueState__9JOBPURSUEi(p,-1);
   break;
  case 5:
   if(!FJobDone(p)&&!func_00209098(p->actor))SetPursueState__9JOBPURSUEi(p,3);
   break;
  }
 }while(old!=p->state);
 if(p->actor->emit &&old<4 &&old>=0 &&p->actor->time<=g_clock.t &&D_003E1BE8<=g_clock.t)
  RaiseGuardAlarm__FP5GUARDP2LO(p->actor,p->target);
}

typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Integer_Size[sizeof(int)==4?1:-1];
typedef char Qword_Size[sizeof(qword)==16?1:-1];
typedef char C_PrefixSize[sizeof(C)==0x60?1:-1];
typedef char P_PrefixSize[sizeof(P)==0xFC8?1:-1];
