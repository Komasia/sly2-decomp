/* SetDamageState (0x1A0B40): changes an actor's damage reaction (DAMAGE +0x4, ACTOR +0xDF4; -1 none, 0..12). Ends the
 * old one (from -1: Sly's hanging parts' chains fall (gravity (0, 0, -750)), vtable slot 91, velocity zeroed, flash fade
 * off; from 3 / 10 (water): their gravity zeroed), then starts the new one: -1 restores gravity and starts the flash
 * fade; 8 (a deadly launch) keeps flying backward and turns toward where it flies, else becomes 9; 3 / 10 float the
 * parts up (500); 5 / 10 / 11 face the camera; 1 / 2 / 4 / 12 keep the body heading and give it to the pad controller;
 * then the reaction's segment (DAMAGE +0xA0 by state, else the default) is applied with grfapl (0x21: no blend).
 * SafeHouse damage.cpp. */
#include "vtbl.h"
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];void Clear(){bits[0]=bits[1]=bits[2]=0;}};
struct ASEGA{char pad[12];VTENT*vt;};
struct ASEG;
struct COMPONENT;
struct PADCTL{char pad[0x18];float radJoy;};          /* the pad controller: +0x18 the stick's heading */
struct ALOCHAIN{char pad[0x20];U vecGravity;};        /* a part chain: +0x20 its gravity */
struct CHAINSEG{char pad[0x60];ALOCHAIN*pchain;};      /* a chain segment: +0x60 its chain */
struct PART{char pad[0xA8];CHAINSEG*pseg;};           /* a part record: +0xA8 its chain segment */
struct P{char pad0[12];VTENT*vt;char pad10[0x150-0x10];PADCTL*control;char pad154[8];int frozen;char pad160[0x190-0x160];U zero;char pad1A0[8];float yaw;int pad1AC;U forward;char pad1C0[0x1030-0x1C0];ASEGA*asega;COMPONENT*component;char pad1038[0x19B8-0x1038];PART*first;PART*second;};
/* DAMAGE (ACTOR +0xDF0): SafeHouse actor.h */
struct DAMAGE{P*actor;int mode;float tStart;char padC[0x98-12];float tFlashFade;int pad9C;ASEG*apasegReaction[13];ASEG*Default(int next){ASEG**base=apasegReaction;int offset=next<8?0:0x20;return *(ASEG**)((char*)base+offset);}};
#define CID_SLY 0x35
#define VT_SET_SLY_MODE 91          /* SafeHouse: SetSlyMode (Sly 0x18D548) */
#define VT_START_REACTION 90
#define VT_VEL_ALO_POS 33           /* VelAloPos */
#define VT_SET_ANG_VELOCITY 36      /* SetAloAngVelocityTo */
#define GRFAPL_NO_BLEND 0x21
#include "clock.h"
struct CM{char pad[0x90];U position;};
struct POLY{float a,b,c;};
struct LIMIT{float lo,hi;};
extern "C"{
 extern CM g_cm;
 extern U g_vecGravityFall asm("D_002BFA00");   /* (0, 0, -750) */
 extern U g_vecGravityWater asm("D_002BFA10");  /* (0, 0, 500) */
 extern U g_vecZero asm("D_002A2DD0");
 extern POLY g_polyLaunchBlend asm("D_002BFA20");  /* -1 + 0.004 |v.xy| */
 extern LIMIT g_lmZeroOne;
 extern float g_flMax asm("D_002A6720");   /* FLT_MAX */
 int FIsBasicDerivedFrom(P*,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
 float atan2f(float,float) asm("atan2f");
 float RadNormalize(float) asm("RadNormalize__Ff");
 void SetStepPhysHeading(P*,float) asm("SetStepPhysHeading__FP3ALOf");
 void TurnActorNow(P*) asm("TurnActorNow__FP5ACTOR");
 void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(P*,qword);
 qword PosOfLo(P*) asm("PosOfLo__FP2LO");
 float RadStepHeading(P*) asm("RadStepHeading__FP4STEP");
 void MarkAloDirty(P*) asm("MarkAloDirty__FP3ALO");
 void RetractAsegaPp(ASEGA**) asm("RetractAsegaPp__FPP5ASEGA");
 void ClearSmaHandle(COMPONENT**) asm("ClearSmaHandle__FPP3SMA");
 void ApplyAsegCur(ASEG*,P*,float,float,int,ASEGA**) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
 void ReplaceSmaHandle(void*,P*,int,void*,COMPONENT**) asm("ReplaceSmaHandle__FP2SMi3OIDiPP3SMA");
}
static inline qword Vector(P*p){VTENT*v=&p->vt[VT_VEL_ALO_POS];return ((qword(*)(P*))v->pfn)((P*)VT_THIS(p, v));}
static inline void SetVector(P*p,qword q){VTENT*v=&p->vt[VT_SET_ANG_VELOCITY];((void(*)(P*,qword))v->pfn)((P*)VT_THIS(p, v),q);}
static inline void Invoke(P*p,int slot){VTENT*v=&p->vt[slot];((void(*)(P*))v->pfn)((P*)VT_THIS(p, v));}
static inline qword Position(){
 register CM*manager __asm__("$2")=&g_cm;
 register qword value __asm__("$2");
 __asm__("lq %0,%1":"=r"(value):"m"(manager->position.q));
 return value;
}
static inline qword From(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline float X(qword a){int word;float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline qword Difference(U*a,qword b,DAMAGE*c,P*&actor){
 register qword x __asm__("vf1"),y __asm__("vf2");register P*owner __asm__("$4");
 __asm__("lqc2 %0,%3\n\tqmtc2.ni %4,%1\n\tlw %2,%5\n\tvsub.xyzw %0,%0,%1":"=&j"(x),"=&j"(y),"=r"(owner):"m"(a->q),"r"(b),"m"(c->actor));
 actor=owner;return x;
}
static inline qword Difference1(U*a,qword b,DAMAGE*c,P*&actor){
 register qword x __asm__("vf4"),y __asm__("vf1");register P*owner __asm__("$4");
 __asm__("qmtc2.ni %4,%1\n\tlw %2,%5\n\tlqc2 %0,%3\n\tvsub.xyzw %0,%0,%1":"=&j"(x),"=&j"(y),"=r"(owner):"m"(a->q),"r"(b),"m"(c->actor));
 actor=owner;return x;
}
static inline float ClampKnownLower(float value,float lo,LIMIT*range){
 register float hi __asm__("$f1")=range->hi;
 if(value<lo)return lo;
 if(hi<value)return hi;
 return value;
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char POLY_Size[sizeof(POLY)==12?1:-1];
typedef char LIMIT_Size[sizeof(LIMIT)==8?1:-1];
typedef char DAMAGE_actor_Offset[FIELD_OFFSET(DAMAGE,actor)==0?1:-1];
typedef char DAMAGE_mode_Offset[FIELD_OFFSET(DAMAGE,mode)==4?1:-1];
typedef char DAMAGE_tStart_Offset[FIELD_OFFSET(DAMAGE,tStart)==8?1:-1];
typedef char DAMAGE_tFlashFade_Offset[FIELD_OFFSET(DAMAGE,tFlashFade)==152?1:-1];
typedef char DAMAGE_apasegReaction_Offset[FIELD_OFFSET(DAMAGE,apasegReaction)==160?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_control_Offset[FIELD_OFFSET(P,control)==336?1:-1];
typedef char P_frozen_Offset[FIELD_OFFSET(P,frozen)==348?1:-1];
typedef char P_zero_Offset[FIELD_OFFSET(P,zero)==400?1:-1];
typedef char P_yaw_Offset[FIELD_OFFSET(P,yaw)==424?1:-1];
typedef char P_forward_Offset[FIELD_OFFSET(P,forward)==432?1:-1];
typedef char P_asega_Offset[FIELD_OFFSET(P,asega)==4144?1:-1];
typedef char P_component_Offset[FIELD_OFFSET(P,component)==4148?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(P,first)==6584?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(P,second)==6588?1:-1];
typedef char PADCTL_radJoy_Offset[FIELD_OFFSET(PADCTL,radJoy)==24?1:-1];
typedef char PART_pseg_Offset[FIELD_OFFSET(PART,pseg)==168?1:-1];
typedef char CHAINSEG_pchain_Offset[FIELD_OFFSET(CHAINSEG,pchain)==96?1:-1];
typedef char ALOCHAIN_vecGravity_Offset[FIELD_OFFSET(ALOCHAIN,vecGravity)==32?1:-1];
typedef char CM_position_Offset[FIELD_OFFSET(CM,position)==144?1:-1];
typedef char POLY_a_Offset[FIELD_OFFSET(POLY,a)==0?1:-1];
typedef char POLY_b_Offset[FIELD_OFFSET(POLY,b)==4?1:-1];
typedef char POLY_c_Offset[FIELD_OFFSET(POLY,c)==8?1:-1];
typedef char LIMIT_lo_Offset[FIELD_OFFSET(LIMIT,lo)==0?1:-1];
typedef char LIMIT_hi_Offset[FIELD_OFFSET(LIMIT,hi)==4?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char qword_Alignment[__alignof__(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char short_Size[sizeof(short)==2?1:-1];
typedef char ASEGA_Prefix_Size[sizeof(ASEGA)==0x10?1:-1];
typedef char PADCTL_Prefix_Size[sizeof(PADCTL)==0x1C?1:-1];
typedef char ALOCHAIN_Prefix_Size[sizeof(ALOCHAIN)==0x30?1:-1];
typedef char CHAINSEG_Prefix_Size[sizeof(CHAINSEG)==0x64?1:-1];
typedef char PART_Prefix_Size[sizeof(PART)==0xAC?1:-1];
typedef char P_Prefix_Size[sizeof(P)==0x19C0?1:-1];
typedef char DAMAGE_Prefix_Size[sizeof(DAMAGE)==0xD4?1:-1];
typedef char CM_Prefix_Size[sizeof(CM)==0xA0?1:-1];
// name: SafeHouse port (SetDamageState)
extern "C" void SetDamageState__FP5ACTORi(DAMAGE*pdmg,int next){
 U velocity,camera0,camera1;
 if(next==pdmg->mode)return;
 switch(pdmg->mode){
 case -1:
  if(FIsBasicDerivedFrom(pdmg->actor,CID_SLY)){
   P*actor=pdmg->actor;actor->first->pseg->pchain->vecGravity=g_vecGravityFall;
   actor->second->pseg->pchain->vecGravity=g_vecGravityFall;
  }
  Invoke(pdmg->actor,VT_SET_SLY_MODE);
  pdmg->actor->zero.Clear();pdmg->actor->frozen=0;pdmg->tFlashFade=g_flMax;
  break;
 case 3:case 10:
  if(FIsBasicDerivedFrom(pdmg->actor,CID_SLY))pdmg->actor->first->pseg->pchain->vecGravity.Clear();
  break;
 }
 ASEG*paseg=0;int grfapl=1;
 switch(next){
 case -1:
  if(FIsBasicDerivedFrom(pdmg->actor,CID_SLY)){
   P*actor=pdmg->actor;actor->first->pseg->pchain->vecGravity.Clear();actor->second->pseg->pchain->vecGravity.Clear();
  }
  pdmg->actor->frozen=1;pdmg->tFlashFade=g_clock.t;break;
 case 8:
  {qword moving=Vector(pdmg->actor);P*actor=pdmg->actor;
  register qword mv __asm__("vf4")=From(moving),axis __asm__("vf1"),dot __asm__("vf2"),one __asm__("vf3");float threshold;
  __asm__("li.s %0,%F2\n\tlqc2 %1,%3":"=&f"(threshold),"=j"(axis):"F"(-250.0f),"m"(actor->forward.q));
  __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(dot),"=&j"(one):"j"(mv),"j"(axis));
  if(X(dot)>threshold)next=9;
  else{
   register qword v __asm__("vf2")=From(Vector(actor));
   float fraction,lower;register LIMIT*range __asm__("$2");
   __asm__("lui $3,%%hi(%5)\n\tvmul.xy $vf1,%4,%4\n\tvaddy.x $vf1,$vf1,$vf1y\n\taddiu %2,$3,%%lo(%5)\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tlwc1 $f1,8(%2)\n\tqmfc2.ni $4,$vf1\n\tlwc1 $f2,4(%2)\n\tmtc1 $4,$f0\n\tlwc1 %0,%%lo(%5)($3)\n\tmul.s $f1,$f0,$f1\n\tlui %2,%%hi(%6)\n\tlwc1 %1,%%lo(%6)(%2)\n\tsqc2 %4,%3\n\taddiu %2,%2,%%lo(%6)\n\tadd.s $f2,$f2,$f1\n\tmul.s $f0,$f0,$f2\n\tadd.s %0,%0,$f0":"=&f"(fraction),"=&f"(lower),"=&r"(range),"=m"(velocity.q):"j"(v),"i"(&g_polyLaunchBlend),"i"(&g_lmZeroOne):"$3","$4","$f0","$f1","$f2","vf1","memory");
   float blend=ClampKnownLower(fraction,lower,range);
   float angle=atan2f(velocity.f[1],velocity.f[0])+3.1415927f;
   angle=RadNormalize(angle-pdmg->actor->yaw);
   SetStepPhysHeading(pdmg->actor,pdmg->actor->yaw+angle*blend);
   TurnActorNow(pdmg->actor);
  }}
 case 9:paseg=pdmg->apasegReaction[next];grfapl=GRFAPL_NO_BLEND;break;
 case 10:
  camera0.q=Position();
  {P*owner;qword direction=Difference(&camera0,PosOfLo(pdmg->actor),pdmg,owner);SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(owner,direction);}
  grfapl=GRFAPL_NO_BLEND;
 case 3:
  paseg=pdmg->apasegReaction[next];
  if(FIsBasicDerivedFrom(pdmg->actor,CID_SLY))pdmg->actor->first->pseg->pchain->vecGravity=g_vecGravityWater;
  break;
 case 5:case 11:
  camera1.q=Position();
  {P*owner;qword direction=Difference1(&camera1,PosOfLo(pdmg->actor),pdmg,owner);SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(owner,direction);}
  if(next==11)grfapl=GRFAPL_NO_BLEND;
  paseg=pdmg->apasegReaction[next];break;
 case 0:case 6:case 7:paseg=pdmg->apasegReaction[next];break;
 case 4:case 12:
  SetVector(pdmg->actor,g_vecZero.q);
  SetStepPhysHeading(pdmg->actor,RadStepHeading(pdmg->actor));
  pdmg->actor->control->radJoy=pdmg->actor->yaw;
  if(next==12)grfapl=GRFAPL_NO_BLEND;
  paseg=pdmg->apasegReaction[next];break;
 case 1:case 2:
  grfapl=0;
  SetStepPhysHeading(pdmg->actor,RadStepHeading(pdmg->actor));
  pdmg->actor->control->radJoy=pdmg->actor->yaw;paseg=pdmg->apasegReaction[next];break;
 }
 MarkAloDirty(pdmg->actor);
 pdmg->mode=next;pdmg->tStart=g_clock.t;
 if(next!=-1){
  if(!paseg)paseg=pdmg->Default(next);
  RetractAsegaPp(&pdmg->actor->asega);ClearSmaHandle(&pdmg->actor->component);
  ApplyAsegCur(paseg,pdmg->actor,0.0f,1.0f,grfapl,&pdmg->actor->asega);
  ReplaceSmaHandle(0,pdmg->actor,-1,0,&pdmg->actor->component);
  Invoke(pdmg->actor,VT_START_REACTION);
 }
}
