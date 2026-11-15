/* UpdateActorWater (0x1A2460): the actor in the water (ACTOR +0x108C): if its point (+0x10A0 above its position, 10
 * lower in the reactions 3 / 10) is inside the water (vtable slot 73), falling or standing (no jump, no reaction 7) it
 * takes the water's contact (filter +0x188, state +0x184); then the splash points (+0x1090, count +0x1094) not splashed
 * in the last 0.05 s that cross the surface within a frame make the water effect's (+0x174) burst at the surface
 * (vtable slot 51, message 4). SafeHouse damage.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M4 {U r[4];};
struct P;
struct EFFECT {char pad[0xC];VTENT*vt;};
struct L {char pad[0xC];VTENT*vt;char pad10[0x164];EFFECT*effect;char pad178[0xC];int nStateContact,grfContact;};  /* the water (ALO): its effect, the contact it gives */
struct ENTRY{P*object;float time;};  /* a splash point: its object, its last splash */
struct P {char pad[0xC];VTENT*vt;char pad10[0x2CC];int state;char pad2E0[0xB14];int mode;char padDF8[0x294];L*link;ENTRY*entries;int count;float pad1098[2];float height;};
struct CTMSG {L*ploSender;int pad4;P*ploReceiver;int grfFilter,nState;char pad14[0xC];U pos,vec;char pad40[0x20];};  /* SafeHouse so.h CTMSG */
struct MSG {int type;char pad4[0x1C];U position;};  /* the effect's message (type 4: a burst at position) */
#define VT_CONTAINS_POINT 73
#define VT_EFFECT_MESSAGE 51
#define VT_VEL_ALO_POS 33
#define VT_FRAME 32
#include "clock.h"
extern "C" qword PosOfLo(P*) asm("PosOfLo__FP2LO");
extern "C" void*s1_memset(void*,int,int) asm("memset");
extern "C" P*PaloAcceptContact(CTMSG*) asm("PaloAcceptContact__FP5CTMSG");
extern "C" int FWaterSurfaceUnder(P*,L*,qword*) asm("FWaterSurfaceUnder__FP5ACTORP3ALOP6VECTOR");
extern "C" void func_002309E8(void*,void*,M4*,M4*,float);
extern "C" M4 MulMatrix4(const M4*,const M4*) asm("MulMatrix4__FP7MATRIX4T0Pv");
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline qword Direction(P*p){return ((qword(*)(void*))p->vt[VT_VEL_ALO_POS].pfn)(VT_THIS(p, &p->vt[VT_VEL_ALO_POS]));}
// name: SafeHouse port (UpdateActorWater)
extern "C" void UpdateActorWater__FP5ACTOR(P*pactor){
 U pos;
 int fIn;
 if(pactor->link){
  pos.q=PosOfLo(pactor);
  pos.f[2]+=pactor->height;
  if(pactor->mode==3||pactor->mode==10)pos.f[2]-=10.0f;
  L*link=pactor->link;
  fIn=((int(*)(void*,qword))link->vt[VT_CONTAINS_POINT].pfn)(VT_THIS(link, &link->vt[VT_CONTAINS_POINT]),pos.q);
 }else fIn=0;
 if(!fIn)return;
 if(pactor->link->nStateContact){
  int fContact=0;
  if(Z(Direction(pactor))<0.0f||(pactor->state==-1&&pactor->mode!=7))fContact=1;
  if(fContact){
   CTMSG ctm;
   s1_memset(&ctm,0,sizeof(ctm));
   ctm.ploSender=pactor->link;
   ctm.ploReceiver=pactor;
   ctm.grfFilter=pactor->link->grfContact;
   ctm.nState=pactor->link->nStateContact;
   ctm.pos.q=PosOfLo(pactor);
   ctm.vec.q=Direction(pactor);
   (void)PaloAcceptContact(&ctm);
  }
 }
 if(!pactor->link->effect)return;
 if(!FWaterSurfaceUnder(pactor,pactor->link,&pos.q))return;
 int i=0;
 if(pactor->count>0){
 U position;
 M4 predicted,base;
 M4*pbase=&base;
 M4*ppred=&predicted;
 // Preserve the saved register for the predicted position.
 register U*predpos __asm__("$20")=&predicted.r[3];
 for(;i<pactor->count;i++){
  ENTRY*entry=&pactor->entries[i];
  if(g_clock.t-entry->time<0.05f)continue;
  P*object=entry->object;
  position.q=PosOfLo(object);
  void*frame=((void*(*)(void*,M4*))object->vt[VT_FRAME].pfn)(VT_THIS(object, &object->vt[VT_FRAME]),pbase);
  func_002309E8(frame,0,ppred,0,g_clock.dt);
  predicted=MulMatrix4(ppred,pbase);
  int crossed=0;
  if(pos.f[2]<=position.f[2]){if(predpos->f[2]<=pos.f[2])crossed=1;}
  else if(pos.f[2]<=predpos->f[2])crossed=1;
  if(crossed){
   MSG msg;
   msg.position=position;
   msg.position.f[2]=pos.f[2];
   msg.type=4;
   EFFECT*effect=pactor->link->effect;
   ((void(*)(void*,MSG*))effect->vt[VT_EFFECT_MESSAGE].pfn)(VT_THIS(effect, &effect->vt[VT_EFFECT_MESSAGE]),&msg);
   entry->time=g_clock.t;
  }
 }
}
}
