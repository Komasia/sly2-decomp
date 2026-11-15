/* FAcceptDamage (0x1A19A0): the actor's damage controller accepts a hit (a contact message, vtable slot 75): a fatal hit
 * (0x1A2358) costs 0x8000; else immune kinds (slot 76) are refused, a hiding actor (+0x4C8 == 1) passes the hit to its
 * hiding spot, and the change is 0 for an actor with +0x29C set or while flashing, else scaled (NScaleDamage). Healing
 * (0x100000) only adds health while some is left (and plays the healing clip), else it becomes a plain launch. A shrunk
 * guard's hit is halved. Then: the actor's state machine is told (slot 88), fragile carried booty is dropped, task
 * event 15 is broadcast, the hit is kept (DAMAGE +0x30), the health counter updated and the flash started, and the
 * reaction by kind starts (with a cry when launched upward); finally the hit's noise. SafeHouse damage.cpp. */
#include "vtbl.h"
#include "cid.h"
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
struct P;
struct C;
typedef void(C::*ACTION)();
struct BOOTYREC{int a,b,fFragile;};  /* the carried booty's record: +0x8 fragile */
struct LOOT{char pad[0x158];BOOTYREC*prec;};  /* the booty an actor carries (ACTOR +0x11A8) */
struct P{char pad0[12];VTENT*vt;char pad10[0x29C-0x10];int guard;char pad2A0[0x4C8-0x2A0];int mode;char pad4CC[8];P*delegate;char pad4D8[0xFBC-0x4D8];int state;char padFC0[0x11A8-0xFC0];LOOT*widget;};
struct CTMSG{P*ploSender;int pad4,pad8;int grfFilter;int dn;char pad14[0x30-0x14];int vecX,vecY,vecZ;char pad3C[0x60-0x3C];}__attribute__((aligned(16)));  /* the hit (SafeHouse so.h CTMSG): its kind, the counter's change, its velocity */
/* DAMAGE (ACTOR +0xDF0; include/h5_damage.h layout) */
struct C{P*actor;int nState;char pad8[8];int*pcount;char pad14[8];ACTION pmfNext;char pad24[0x30-0x24];CTMSG msg;int nFlash;float tFlash,tFlashFade;char pad9C[0x108-0x9C];void*pasegHeal;void*pasegaHeal;
 void Reaction() __asm__("NextGetUp__FP5ACTOR");
 void Special() __asm__("NextSpecial__FP5ACTOR");
 void Stop() __asm__("NextStunned__FP5ACTOR");
 void Finish() __asm__("NextRecover__FP5ACTOR");
};
#include "clock.h"
struct SW{char pad[0x4038];int channel;};  /* the world: +0x4038 its noise channel */
extern "C"{
 extern char D_002DE578[],g_game[];
 extern SW g_sw;
 extern qword g_vecZero asm("D_002A2DD0");
 extern qword g_vecDamageDown asm("D_002BFB10");  /* (0, 0, -1000) */
 int func_001A2358(C*,CTMSG*);
 int NScaleDamage(void*,int) asm("NScaleDamage__FPvi");
 void ApplyAsegCur(void*,P*,float,float,int,void**) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
 int FIsBasicDerivedFrom(P*,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
 void DropActorBooty(P*) asm("DropActorBooty__FP5ACTORii");
 void BroadcastTaskEvent(void*,int,P*) asm("BroadcastTaskEvent__FP2SWiP2LO");
 void func_001A15B0(C*,ACTION);
 void ApplyDamageVelocity(C*) asm("ApplyDamageVelocity__FP5ACTOR");
 void SetDamageState(C*,int) asm("SetDamageState__FP5ACTORi");
 int func_00132EA0(P*);
 void*PsndNewPlain(int) asm("PsndNewPlain__Fi");
 void SetSource(void*,P*) asm("SetSource__4CSndPv");
 qword PosOfLo(P*) asm("PosOfLo__FP2LO");
 void*func_00156698(int,qword,P*);
}
static inline int Add32(int a,int b){return (int)((unsigned)a+(unsigned)b);}
static inline int Reject(P*p,int flags){VTENT*v=&p->vt[76];return ((int(*)(P*,int))v->pfn)((P*)VT_THIS(p, v),flags);}
static inline int Delegate(P*p,CTMSG*r){VTENT*v=&p->vt[75];return ((int(*)(P*,CTMSG*))v->pfn)((P*)VT_THIS(p, v),r);}
static inline qword Vector(P*p,int slot){VTENT*v=&p->vt[slot];return ((qword(*)(P*))v->pfn)((P*)VT_THIS(p, v));}
static inline void SetVector(P*p,int slot,qword value){VTENT*v=&p->vt[slot];((void(*)(P*,qword))v->pfn)((P*)VT_THIS(p, v),value);}
static inline void Notify(P*p,int value){VTENT*v=&p->vt[88];((void(*)(P*,int))v->pfn)((P*)VT_THIS(p, v),value);}
static inline float Z(qword value){register int word __asm__("$9");float result;__asm__("pextuw %0,$zero,%1":"=r"(word):"r"(value));__asm__("mtc1 %1,%0":"=f"(result):"r"(word));return result;}
typedef char CTMSG_Size[sizeof(CTMSG)==96?1:-1];
typedef char ACTION_Size[sizeof(ACTION)==8?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==0?1:-1];
typedef char C_nState_Offset[FIELD_OFFSET(C,nState)==4?1:-1];
typedef char C_pcount_Offset[FIELD_OFFSET(C,pcount)==16?1:-1];
typedef char C_pmfNext_Offset[FIELD_OFFSET(C,pmfNext)==28?1:-1];
typedef char C_msg_Offset[FIELD_OFFSET(C,msg)==48?1:-1];
typedef char C_nFlash_Offset[FIELD_OFFSET(C,nFlash)==144?1:-1];
typedef char C_tFlash_Offset[FIELD_OFFSET(C,tFlash)==148?1:-1];
typedef char C_tFlashFade_Offset[FIELD_OFFSET(C,tFlashFade)==152?1:-1];
typedef char C_pasegHeal_Offset[FIELD_OFFSET(C,pasegHeal)==264?1:-1];
typedef char C_pasegaHeal_Offset[FIELD_OFFSET(C,pasegaHeal)==268?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_guard_Offset[FIELD_OFFSET(P,guard)==668?1:-1];
typedef char P_mode_Offset[FIELD_OFFSET(P,mode)==1224?1:-1];
typedef char P_delegate_Offset[FIELD_OFFSET(P,delegate)==1236?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(P,state)==4028?1:-1];
typedef char P_widget_Offset[FIELD_OFFSET(P,widget)==4520?1:-1];
typedef char LOOT_prec_Offset[FIELD_OFFSET(LOOT,prec)==344?1:-1];
typedef char BOOTYREC_fFragile_Offset[FIELD_OFFSET(BOOTYREC,fFragile)==8?1:-1];
typedef char CTMSG_ploSender_Offset[FIELD_OFFSET(CTMSG,ploSender)==0?1:-1];
typedef char CTMSG_grfFilter_Offset[FIELD_OFFSET(CTMSG,grfFilter)==12?1:-1];
typedef char CTMSG_dn_Offset[FIELD_OFFSET(CTMSG,dn)==16?1:-1];
typedef char CTMSG_vecX_Offset[FIELD_OFFSET(CTMSG,vecX)==48?1:-1];
typedef char CTMSG_vecY_Offset[FIELD_OFFSET(CTMSG,vecY)==52?1:-1];
typedef char CTMSG_vecZ_Offset[FIELD_OFFSET(CTMSG,vecZ)==56?1:-1];
typedef char SW_channel_Offset[FIELD_OFFSET(SW,channel)==16440?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char unsigned_Size[sizeof(unsigned)==4?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char short_Size[sizeof(short)==2?1:-1];
typedef char CTMSG_Alignment[__alignof__(CTMSG)==16?1:-1];
typedef char C_Prefix_Size[sizeof(C)==0x110?1:-1];
typedef char P_Prefix_Size[sizeof(P)==0x11AC?1:-1];
typedef char LOOT_Prefix_Size[sizeof(LOOT)==0x15C?1:-1];
typedef char BOOTYREC_Size[sizeof(BOOTYREC)==12?1:-1];
typedef char SW_Prefix_Size[sizeof(SW)==0x403C?1:-1];
// name: SafeHouse port (FAcceptDamage)
extern "C" int FAcceptDamage__FP5ACTORP5CTMSG(C*pdmg,CTMSG*pctm){
 CTMSG accepted;int delta;
 if(func_001A2358(pdmg,pctm)){
  if((unsigned)pdmg->nState-8u<5u)return 0;
  delta=-32768;goto notify;
 }
 if(Reject(pdmg->actor,pctm->grfFilter))return 0;
 if(pdmg->actor->mode==1)return Delegate(pdmg->actor->delegate,pctm);
 if(pdmg->actor->guard)delta=0;
 else if(pdmg->nFlash==1)delta=0;
 else delta=NScaleDamage(D_002DE578,pctm->dn);
 if(pctm->grfFilter==0x100000){
  if(Add32(*pdmg->pcount,delta)>0){
   if(pdmg->nFlash!=1){pdmg->nFlash=0;pdmg->tFlash=pdmg->tFlashFade=g_clock.t;}
   *pdmg->pcount=Add32(*pdmg->pcount,delta);
   if(pdmg->pasegHeal)ApplyAsegCur(pdmg->pasegHeal,pdmg->actor,0.0f,1.0f,1,&pdmg->pasegaHeal);
   goto sound;
  }
  register CTMSG*destination __asm__("$2");__asm__("daddu %0,%1,$zero":"=r"(destination):"r"(&accepted));
  *destination=*pctm;pctm=&accepted;
  accepted.grfFilter=0x200;
  __asm__("sw $zero,4(%3)\n\tsw $zero,8(%3)\n\tsw $zero,%2":"=m"(accepted.vecY),"=m"(accepted.vecZ),"=m"(accepted.vecX):"r"(&accepted.vecX));
 }
 if(pctm->ploSender&&FIsBasicDerivedFrom(pctm->ploSender,CID_STEPGUARD)){
  if(pctm->ploSender->state==8||pctm->ploSender->state==13)delta/=2;
 }
notify:
 {
  Notify(pdmg->actor,3);
  LOOT*widget=pdmg->actor->widget;
  if(widget&&(widget->prec->fFragile||Add32(*pdmg->pcount,delta)<=0))DropActorBooty(pdmg->actor);
  BroadcastTaskEvent(g_game,0xF,pctm->ploSender);
  pdmg->msg=*pctm;pdmg->msg.dn=delta;func_001A15B0(pdmg,0);
  int n=Add32(*pdmg->pcount,pdmg->msg.dn);*pdmg->pcount=n>=0?n:0;
  if(*pdmg->pcount>0){pdmg->nFlash=1;pdmg->tFlash=g_clock.t;}
  switch(pctm->grfFilter){
  case 0x100:case 0x200:{
   ApplyDamageVelocity(pdmg);
   if(Z(Vector(pdmg->actor,33))>400.0f){
    int effect=-1;
    switch(func_00132EA0(pdmg->actor)){case 0x35:effect=0x69;break;case 0x36:effect=0x84;break;case 0x37:effect=0x83;break;}
    P*actor=pdmg->actor;void*created=PsndNewPlain(effect);SetSource(created,actor);
   }
   func_001A15B0(pdmg,&C::Reaction);break;
  }
  case 0x8000:SetDamageState(pdmg,7);func_001A15B0(pdmg,&C::Special);break;
  case 0x800:case 0x1000:
   SetVector(pdmg->actor,35,g_vecZero);SetVector(pdmg->actor,36,g_vecZero);
   SetDamageState(pdmg,pctm->grfFilter==0x800?1:2);func_001A15B0(pdmg,&C::Stop);break;
  case 0x2000:if(*pdmg->pcount>0){SetDamageState(pdmg,3);func_001A15B0(pdmg,&C::Finish);}else SetDamageState(pdmg,10);break;
  case 0x400:SetVector(pdmg->actor,35,g_vecDamageDown);if(*pdmg->pcount>0)SetDamageState(pdmg,4);else SetDamageState(pdmg,12);break;
  case 0x4000:
   if(*pdmg->pcount>0){SetDamageState(pdmg,5);func_001A15B0(pdmg,&C::Finish);}else SetDamageState(pdmg,11);break;
  case 0x40:ApplyDamageVelocity(pdmg);func_001A15B0(pdmg,&C::Reaction);break;
  }
 }
sound:
 register SW*game __asm__("$16")=&g_sw;
 qword point=PosOfLo(pdmg->actor);int channel=game->channel;
 (void)func_00156698(channel,point,pdmg->actor);
 return 1;
}
