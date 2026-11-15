/* JOBB1::SetState (a launched guard): leaving the start (no state) makes the guard light (mass * D_002BE6FC), leaving
 * landed rewinds the entry; leaving rising / falling for another state drops the launch's target controller and puts
 * the guard's transforms back (mode 2); entering or leaving a contact state (0, 4, 5) recomputes the world's object
 * filter and drops the contacts. Then: none: the mass back, the move's state 1; rising: the owner's launch target
 * D_002BE700 s ahead (its vt slot 96), the velocity set to reach it (BlendSet), a target controller (arrival now +
 * D_002BE700) when there is none, tracking while the owner holds this guard (+0x10DC), the pad's rumble when the
 * guard's thrower is the current player; landed / drawn: the entry seeks its event 0x3C / 0x173.
 * SafeHouse port (aihit.cpp JOBB1::SetState). Register-pinned asm reproduces the matched schedule.
 * Layout: SafeHouse port (aijobs.h JOBB1, LAUNCHTARGET; KINDE +0x4 its ASEG, +0x8 its ASEGA; GUARD +0x58 / +0x5C
 * the position / rotation transforms, +0xE8 its SO state (+0xD0 the mass), +0x334, +0x10DC what it holds). */
#include "vtbl.h"
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];void Assign(const U&v){q=v.q;}};
union F{float value;int bits;};
struct XF{char pad[0xA0];void*pxfRef;};
struct SOST{char pad[0xD0];float m;};
struct GUARD{char pad0[12];VTENT*vt;char pad10[0x58-0x10];XF*pxfPos;XF*pxfRot;char pad60[0xE8-0x60];SOST*psost;char padEC[0x334-0xEC];int n334;char pad338[0x10DC-0x338];GUARD*plo10DC;};
struct ASEGA;
struct ENTRY{float value;int kind,key,pad;};
struct KINDE{char pad0[4];void*paseg;ASEGA*pasega;};
struct CTRL;
struct LAUNCHTARGET{int fActive;float sRadius,dz;int pad;U pos,vel;};
struct JOBB1{char pad0[0x10];GUARD*pguard;char pad14[0x40-0x14];KINDE*pkinde;char pad44[12];int stLaunch;float tLaunch;int nLaunch;GUARD*ploOwner;int fTrack;CTRL*pctrlTarget;};
#include "clock.h"
extern "C"{
 extern float D_002BE6FC,D_002BE700,D_002BE704;
 extern F D_002BE708;
 extern U g_normalZ;
 extern char g_sw[],g_joy[];
 void SetSoMass(GUARD*,float) asm("SetSoMass__FP2SOf");
 void SetAsegaTime(ASEGA*,int,float,float) asm("SetAsegaTime__FP5ASEGAiff");
 void DeleteCtrl(CTRL**) asm("DeleteCtrl__FPP4CTRL");
 void SetXfMode(GUARD*,XF*,int) asm("SetXfMode__FP3ALOP2XFi");
 void RecalcSwOxfFilterForObject(void*,GUARD*) asm("RecalcSwOxfFilterForObject__FP2SWP2SO");
 void DetachAloContacts(GUARD*) asm("DetachAloContacts__FP3ALO");
 void SetMoveState(JOBB1*,int) asm("SetMoveState__7JOBMOVEi");
 void GetTarget(JOBB1*,LAUNCHTARGET*,U*,U*) asm("GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2");
 qword PosOfLo(GUARD*) asm("PosOfLo__FP2LO");
 qword PosConvertXfs(void*,void*,qword) asm("PosConvertXfs__FP2XFT0G9VU_VECTOR");
 qword VecConvertXfs(void*,void*,qword) asm("VecConvertXfs__FP2XFT0G9VU_VECTOR");
 CTRL*PctrlNewTarget(GUARD*,XF*,void*,float,qword,qword) asm("PctrlNewTarget__FP3ALOP2XFPvfG9VU_VECTORT4");
 GUARD*PloPlayerPo(void*) asm("PloPlayerPo__FP2SW");
 void TriggerJoyRumbleRumk(void*,int,float) asm("TriggerJoyRumbleRumk__FP3JOY4RUMKf");
 ENTRY*PeventLaunch(void*,int) asm("PeventLaunch__FP5KINDEi");
}
static inline void Request(GUARD*p,LAUNCHTARGET*r,float duration){VTENT*v=&p->vt[96];((void(*)(GUARD*,LAUNCHTARGET*,float))v->pfn)((GUARD*)VT_THIS(p, v),r,duration);}
static inline void BlendSet(JOBB1*p,qword current,U*desired,U*scale,U*scratch){
 register GUARD*pguard __asm__("$7");register VTENT*vt __asm__("$6");register int word __asm__("$4");
 register qword a __asm__("vf1"),b __asm__("vf2"),d __asm__("vf3"),lift __asm__("vf2"),axis __asm__("vf1"),k __asm__("vf4");
 const unsigned gainAddress=0x2BE708;
 register char*gainBase __asm__("$4");
 __asm__("lw %0,%4\n\tqmtc2.ni %5,%1\n\tlqc2 %2,%6\n\tlui %3,%7"
  :"=&r"(pguard),"=j"(b),"=j"(a),"=r"(gainBase)
  :"m"(p->pguard),"r"(current),"m"(desired->q),"i"((gainAddress+0x8000)>>16));
 const unsigned axisLocation=0x2A2DC0;
 register char*axisBase __asm__("$3");
 __asm__("lw %0,%4\n\tvsub.xyzw %1,%5,%6\n\tlw %2,%7\n\tlui %3,%8"
  :"=&r"(vt),"=j"(d),"=r"(word),"=r"(axisBase)
  :"m"(pguard->vt),"j"(a),"j"(b),"m"(*(int*)(gainBase+(short)(gainAddress&0xffff))),"i"((axisLocation+0x8000)>>16));
 register U*axisAddress __asm__("$3");
 __asm__("qmtc2.ni %2,%0\n\taddiu %1,%3,%4"
  :"=j"(lift),"=r"(axisAddress):"r"(word),"r"(axisBase),"i"((short)(axisLocation&0xffff)));
 register int adjustment __asm__("$4");
 register void(*setter)() __asm__("$3");
 __asm__("lqc2 %0,%4\n\tlh %1,%5\n\tlqc2 %2,%6\n\tlw %3,%7"
  :"=j"(axis),"=r"(adjustment),"=j"(k),"=r"(setter)
  :"m"(axisAddress->q),"m"(vt[35].delta),"m"(scale->q),"m"(((void (*)())vt[35].pfn)));
 register qword packed __asm__("$5");
 register GUARD*adjusted __asm__("$4");
 __asm__("vmulax.xyzw $ACC,%3,%0x\n\tvmaddx.xyzw %0,%4,%5x\n\tqmfc2.ni %1,%0\n\taddu %2,%6,%7"
  :"+j"(k),"=r"(packed),"=r"(adjusted):"j"(d),"j"(axis),"j"(lift),"r"(pguard),"r"(adjustment));
 scratch->q=lift;
 ((void(*)(GUARD*,qword))setter)(adjusted,packed);
}
typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Int_Size[sizeof(int)==4?1:-1];
typedef char Float_Size[sizeof(float)==4?1:-1];
typedef char Short_Size[sizeof(short)==2?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char REQUEST_Alignment[__alignof__(LAUNCHTARGET)==16?1:-1];
typedef char C_Size[sizeof(JOBB1)==0x68?1:-1];
typedef char P_Size[sizeof(GUARD)==0x10E0?1:-1];
typedef char GROUP_Size[sizeof(XF)==0xA4?1:-1];
typedef char TUNE_Size[sizeof(SOST)==0xD4?1:-1];
typedef char CONTROL_Size[sizeof(KINDE)==12?1:-1];
typedef char REQUEST_Size[sizeof(LAUNCHTARGET)==48?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char F_Size[sizeof(F)==4?1:-1];
typedef char ENTRY_Size[sizeof(ENTRY)==16?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(JOBB1,pguard)==16?1:-1];
typedef char C_control_Offset[FIELD_OFFSET(JOBB1,pkinde)==64?1:-1];
typedef char C_mode_Offset[FIELD_OFFSET(JOBB1,stLaunch)==80?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(JOBB1,tLaunch)==84?1:-1];
typedef char C_target_Offset[FIELD_OFFSET(JOBB1,ploOwner)==92?1:-1];
typedef char C_owned_Offset[FIELD_OFFSET(JOBB1,fTrack)==96?1:-1];
typedef char C_delta_Offset[FIELD_OFFSET(JOBB1,pctrlTarget)==100?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(GUARD,vt)==12?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(GUARD,pxfPos)==88?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(GUARD,pxfRot)==92?1:-1];
typedef char P_tuning_Offset[FIELD_OFFSET(GUARD,psost)==232?1:-1];
typedef char P_attention_Offset[FIELD_OFFSET(GUARD,n334)==820?1:-1];
typedef char P_owner_Offset[FIELD_OFFSET(GUARD,plo10DC)==4316?1:-1];
typedef char GROUP_space_Offset[FIELD_OFFSET(XF,pxfRef)==160?1:-1];
typedef char TUNE_speed_Offset[FIELD_OFFSET(SOST,m)==208?1:-1];
typedef char CONTROL_curves_Offset[FIELD_OFFSET(KINDE,paseg)==4?1:-1];
typedef char CONTROL_asega_Offset[FIELD_OFFSET(KINDE,pasega)==8?1:-1];
typedef char REQUEST_flag_Offset[FIELD_OFFSET(LAUNCHTARGET,fActive)==0?1:-1];
typedef char REQUEST_sRadius_Offset[FIELD_OFFSET(LAUNCHTARGET,sRadius)==4?1:-1];
typedef char REQUEST_dz_Offset[FIELD_OFFSET(LAUNCHTARGET,dz)==8?1:-1];
typedef char REQUEST_point_Offset[FIELD_OFFSET(LAUNCHTARGET,pos)==16?1:-1];
typedef char REQUEST_direction_Offset[FIELD_OFFSET(LAUNCHTARGET,vel)==32?1:-1];
typedef char ENTRY_value_Offset[FIELD_OFFSET(ENTRY,value)==0?1:-1];
typedef char ENTRY_kind_Offset[FIELD_OFFSET(ENTRY,kind)==4?1:-1];
typedef char ENTRY_key_Offset[FIELD_OFFSET(ENTRY,key)==8?1:-1];
static inline int Still(int m){int f=0;if(m==4||m==5||m==0)f=1;return f;}
// name: SafeHouse port (JOBB1::SetState)
extern "C" void SetState__5JOBB1i(JOBB1*p,int next){
 LAUNCHTARGET target;
 U pos,vel,scratch,scale,cached;
 if(next==p->stLaunch)return;
 switch(p->stLaunch){
 case -1:SetSoMass(p->pguard,D_002BE6FC*p->pguard->psost->m);break;
 case 3:if(next!=-1)SetAsegaTime(p->pkinde->pasega,0,0.0f,1.0f);break;
 }
 if((unsigned)p->stLaunch<2&&(unsigned)next>=2){
  DeleteCtrl(&p->pctrlTarget);SetXfMode(p->pguard,p->pguard->pxfPos,2);SetXfMode(p->pguard,p->pguard->pxfRot,2);
 }
 int was=Still(p->stLaunch),now=Still(next);
 p->stLaunch=next;
 if(was!=now){
  const unsigned gameAddress=0x3DD490;
  register char*gameBase __asm__("$4");
  register GUARD*callbackActor __asm__("$5");
  __asm__("lui %0,%2\n\tlw %1,%3":"=&r"(gameBase),"=r"(callbackActor)
   :"i"((gameAddress+0x8000)>>16),"m"(p->pguard));
  RecalcSwOxfFilterForObject(gameBase+(short)(gameAddress&0xffff),callbackActor);
  DetachAloContacts(p->pguard);p->stLaunch=next;
 }
 const unsigned clockAddress=0x2DDED0;
 char*clockHigh;
 register char*clockCarrier __asm__("$19");
 register float newTime __asm__("$f0");
 __asm__("lui %0,%1":"=r"(clockHigh):"i"((clockAddress+0x8000)>>16));
 __asm__("daddu %0,%2,$0\n\tlwc1 %1,%3":"=&r"(clockCarrier),"=f"(newTime)
  :"r"(clockHigh),"m"(*(float*)(clockHigh+(short)(clockAddress&0xffff))));
 p->tLaunch=newTime;
 switch(next){
 case -1:SetSoMass(p->pguard,p->pguard->psost->m/D_002BE6FC);SetMoveState(p,1);break;
 case 0:{
  Request(p->ploOwner,&target,D_002BE700);
  GetTarget(p,&target,&pos,&vel);
  register qword scalar __asm__("$2");
  register GUARD*beforeActor __asm__("$4");
  register float duration __asm__("$f1")=D_002BE700;
  register float factor __asm__("$f0")=D_002BE704;
  __asm__("lq %0,%4\n\tlw %1,%5\n\tdiv.s %2,%2,%6\n\tsq %0,%3\n\tmfc1 %0,%2"
   :"=&r"(scalar),"=&r"(beforeActor),"+f"(factor),"=m"(cached.q)
   :"m"(pos.q),"m"(p->pguard),"f"(duration));
  scratch.q=scalar;scale=scratch;
  qword current=PosOfLo(beforeActor);
  BlendSet(p,current,&cached,&scale,&scratch);
  XF*pxfPos=p->pguard->pxfPos;
  if(!p->pctrlTarget){
   float end=*(float*)(clockCarrier+(short)(clockAddress&0xffff))+D_002BE700;
   qword localPoint=PosConvertXfs(0,pxfPos->pxfRef,pos.q);
   qword localDirection=VecConvertXfs(0,pxfPos->pxfRef,vel.q);
   p->pctrlTarget=PctrlNewTarget(p->pguard,pxfPos,0,end,localPoint,localDirection);
  }
  int fTrack=0;if(target.fActive)fTrack=p->ploOwner->plo10DC==p->pguard;p->fTrack=fTrack;
  if(p->pguard->n334){GUARD*focus=PloPlayerPo(g_sw);if(focus&&p->ploOwner==focus)TriggerJoyRumbleRumk(g_joy,3,0.15f);}
  break;
 }
 case 3:{ENTRY*entry=PeventLaunch(p->pkinde->paseg,0x3C);if(entry)SetAsegaTime(p->pkinde->pasega,0,entry->value,1.0f);break;}
 case 4:case 5:
  if(p->stLaunch==4){ENTRY*entry=PeventLaunch(p->pkinde->paseg,0x173);if(entry)SetAsegaTime(p->pkinde->pasega,0,entry->value,1.0f);}
  break;
 case 1:case 2:break;
 }
}
