#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
struct P;
struct VE{short delta,pad;void(*fn)();};
struct P{char pad0[12];VE*vt;char pad10[0x38C-0x10];P*selected;char pad390[0xE20-0x390];void*extra;};
struct H{char pad0[0x30];P*object;char pad34[16];P*target;char pad48[8];int mode;char pad54[8];P*extra;};
struct STATE{int kind,pad4,pad8,padC;union{qword data[6];struct{P*object;float amount;char pad18[0x60-8];}s;}payload;};
struct C{char pad0[16];P*actor;int pad14;H*helper;char pad1C[0x30-0x1C];STATE state;float started,expires;};
#include "clock.h"
extern "C"{
 extern char g_sw[];
 void Update__5AIJOB(C*);
 int FJobDone(C*) asm("FJobDone__FP5AIJOB");
 int func_00177D20(C*);
 int func_00177D48(C*);
 int FSameMsg(const STATE*,const STATE*) asm("FSameMsg__FP5AIMSGT0");
 void React(C*,const STATE*) asm("React__8JOBREACTP5AIMSG");
 void*s1_memset(void*,int,unsigned int) asm("memset");
 int func_00208B38(P*,P*);
 float func_00208BB0(P*);
 P*PloGuardInterest(P*,P*) asm("PloGuardInterest__FP5GUARDP2LO");
 void SetNoise(H*,P*) asm("SetNoise__14JOBINVESTIGATEP5NOISE");
 int func_00172550(H*);
 int func_00174FB8(H*);
 int FIsBasicDerivedFrom(P*,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
 int func_00171458(H*);
 int func_00175810(H*);
 P*func_00174898(void*);
 qword PosOfLo(P*) asm("PosOfLo__FP2LO");
 P*func_00156B98(void*,int,qword,P*);
 void RemoveNoise(P*) asm("RemoveNoise__FP5NOISE");
 void SendHit(C*,int,P*) asm("SendHit__8JOBREACTii");
 int FDoneB0(H*) asm("FDone__5JOBB0");
 int FDone(H*) asm("FDone__11JOBNAVPOINT");
 int func_0017DE40(H*);
 void NextReaction(C*) asm("NextReaction__8JOBREACT");
}
static inline P*Target(P*p){VE*v=&p->vt[88];return ((P*(*)(P*))v->fn)((P*)((char*)p+v->delta));}
static inline int Mode(P*p){VE*v=&p->vt[77];return ((int(*)(P*))v->fn)((P*)((char*)p+v->delta));}
static inline void Clear(STATE*s){s1_memset(s,0,sizeof(*s));}
static inline void Attack(C*p,STATE*s,P*object){
 if(func_00208B38(p->actor,object)){s->kind=18;s->payload.s.object=object;s->payload.s.amount=func_00208BB0(p->actor);}
 else{s->kind=3;s->payload.s.object=object;}
}
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char STATE_Size[sizeof(STATE)==112?1:-1];
typedef char VE_delta_Offset[FIELD_OFFSET(VE,delta)==0?1:-1];
typedef char VE_fn_Offset[FIELD_OFFSET(VE,fn)==4?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_selected_Offset[FIELD_OFFSET(P,selected)==908?1:-1];
typedef char P_extra_Offset[FIELD_OFFSET(P,extra)==3616?1:-1];
typedef char H_object_Offset[FIELD_OFFSET(H,object)==48?1:-1];
typedef char H_target_Offset[FIELD_OFFSET(H,target)==68?1:-1];
typedef char H_mode_Offset[FIELD_OFFSET(H,mode)==80?1:-1];
typedef char H_extra_Offset[FIELD_OFFSET(H,extra)==92?1:-1];
typedef char STATE_kind_Offset[FIELD_OFFSET(STATE,kind)==0?1:-1];
typedef char STATE_payload_Offset[FIELD_OFFSET(STATE,payload)==16?1:-1];
typedef char STATE_payload_s_object_Offset[FIELD_OFFSET(STATE,payload.s.object)==16?1:-1];
typedef char STATE_payload_s_amount_Offset[FIELD_OFFSET(STATE,payload.s.amount)==20?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==16?1:-1];
typedef char C_helper_Offset[FIELD_OFFSET(C,helper)==24?1:-1];
typedef char C_state_Offset[FIELD_OFFSET(C,state)==48?1:-1];
typedef char C_started_Offset[FIELD_OFFSET(C,started)==160?1:-1];
typedef char C_expires_Offset[FIELD_OFFSET(C,expires)==164?1:-1];
// name: SafeHouse port (JOBREACT::Update)
extern "C" void Update__8JOBREACT(C*p){
 Update__5AIJOB(p);
 while(!FJobDone(p)){
  STATE previous=p->state;
  STATE*current=&p->state;
  switch(p->state.kind){
  case 1:case 16:case 17:{
   STATE next;Clear(&next);
   if(!func_00177D20(p)){
    P*object=Target(p->actor);
    if(object)Attack(p,&next,object);
    else{
     P*selected=PloGuardInterest(p->actor,0);
     if(selected){next.kind=2;next.payload.s.object=selected;}
     else if(p->state.kind==17&&g_clock.t<p->expires)next.kind=17;
     else{if(func_00177D48(p))next.kind=16;else next.kind=1;}
    }
   }else next.kind=12;
   React(p,&next);break;
  }
  case 2:{
   if(func_00177D20(p)){STATE next;Clear(&next);next.kind=12;React(p,&next);}
   else{
    P*object=Target(p->actor);
    if(object){STATE next;Clear(&next);Attack(p,&next,object);React(p,&next);}
    else{
     H*h=p->helper;P*old=h->target;P*selected=PloGuardInterest(p->actor,old);
     if(selected!=old)SetNoise(h,selected);
     else if(func_00172550(h)){STATE next;Clear(&next);next.kind=1;React(p,&next);}
    }
   }
   break;
  }
  case 3:{
   if(func_00177D20(p)){STATE next;Clear(&next);next.kind=12;React(p,&next);}
   else if(func_00174FB8(p->helper)){
    STATE next;Clear(&next);if(FIsBasicDerivedFrom(p->actor,0x3B)){next.kind=13;next.payload.s.object=p->state.payload.s.object;}else{next.kind=4;next.payload.s.object=p->state.payload.s.object;}React(p,&next);
   }
   break;
  }
  case 5:if(func_00171458(p->helper))NextReaction(p);break;
  case 4:{
   H*h=p->helper;
   if(func_00177D20(p)){STATE next;Clear(&next);next.kind=12;React(p,&next);}
   else if(func_00175810(h)){STATE next;Clear(&next);next.kind=1;React(p,&next);}
   else{
    P*object=Target(p->actor);
    if(object!=p->actor->selected){
     STATE next;Clear(&next);
     if(object)Attack(p,&next,object);
     else{
      next.kind=1;P*other=h->object;
      if(other&&FIsBasicDerivedFrom(other,0x34)&&Mode(other)==2){
       P*owner=func_00174898(other->extra);
       if(owner&&owner!=p->actor){next.payload.s.object=owner;next.kind=17;}
      }
     }
     React(p,&next);
    }
   }
   break;
  }
  case 12:{if(!func_00177D20(p)){STATE next;Clear(&next);next.kind=1;React(p,&next);}break;}
  case 0:{STATE next;Clear(&next);next.kind=1;React(p,&next);break;}
  case 8:{
   if(func_00174FB8(p->helper)){
    P*object=func_00156B98(g_sw,0,PosOfLo(p->actor),p->actor);
    STATE next;Clear(&next);next.kind=2;next.payload.s.object=object;React(p,&next);RemoveNoise(object);
   }
   break;
  }
  case 7:{
   H*h=p->helper;
   if(func_00174FB8(h)){
    if(h->mode!=-1){if(h->mode==3)NextReaction(p);}
    else{SendHit(p,-50,h->extra);if(p->state.kind==7)NextReaction(p);}
   }
   break;
  }
  case 6:if(FDoneB0(p->helper))NextReaction(p);break;
  case 9:if(func_00174FB8(p->helper))NextReaction(p);break;
  case 10:if(func_00174FB8(p->helper))NextReaction(p);break;
  case 19:if(FDone(p->helper))NextReaction(p);break;
  case 18:if(func_0017DE40(p->helper))NextReaction(p);break;
  }
  if(FSameMsg(current,&previous))break;
 }
}
