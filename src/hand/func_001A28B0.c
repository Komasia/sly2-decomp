/* ApplyWaterToActor (0x1A28B0): the players' vtable slot 72, the water's push during a physics frame: rising in the
 * jump's state 5 or in reaction 7 nothing (falling: the ALO's ApplyWaterToAlo); in the reactions 3 / 10 held at the
 * surface: the drag toward the water's flow (0x228C18) less the clip's motion (+0x190 in the heading's frame +0x1B0),
 * times +0x10A4, and the height (+0x10A0 above the position) smoothed onto the surface (SMPA +0x10A8) against the
 * gravity; else the ALO's. SafeHouse damage.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct M3 { qword r[3]; };
struct SOST { char pad[0x80]; U dvGravity; };  /* the physics state: +0x80 the gravity */
struct SMPA { float a,b,c,d; };  /* GSmoothA's parameters */
struct P {
 char pad[0xC]; VTENT *vt;
 char pad1[0xE8-0x10]; struct SOST *xE8;
 char pad2[0x190-0xEC]; qword v190;
 char pad3[0x1B0-0x1A0]; struct M3 m1B0;
 char pad4[0x2DC-0x1E0]; int state2DC;
 char pad5[0xDF4-0x2E0]; int stateDF4;
 char pad6[0x10A0-0xDF8]; float height10A0, alpha10A4;
 struct SMPA smp10A8;
};
#include "clock.h"
#define VT_VEL_ALO_POS 33
#define JUMP_STATE_RISE 5
int FWaterSurfaceUnder__FP5ACTORP3ALOP6VECTOR(struct P *p,void *pwater,qword *ppos);
void func_00228C18(void *pwater,qword pos,qword *pvFlow,qword *pv);
void ApplyWaterToAlo__FP3ALOT0(struct P *p,void *pwater);
qword PosOfLo__FP2LO(struct P *p);
float GSmoothA(float pos,float vel,float target,float dt,struct SMPA *psmpa,float *result) asm("GSmoothA__FffffP4SMPAPf");
void AccelAloPos__FP3ALOG9VU_VECTOR(struct P *p,qword v);
static inline qword GetVel(struct P *p) { return ((qword (*)(void *))p->vt[VT_VEL_ALO_POS].pfn)(VT_THIS(p, &p->vt[VT_VEL_ALO_POS])); }
static inline qword Mul(struct M3 *m,const qword *v) { qword r; __asm__("vmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z" : "=j"(r) : "j"(*v),"j"(m->r[0]),"j"(m->r[1]),"j"(m->r[2]));return r; }
static inline qword Add(qword a,qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b));return r; }
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b));return r; }
static inline qword Broadcast(int g) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(g));return r; }
static inline qword Scale(qword v,qword k) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v),"j"(k));return r; }
// name: SafeHouse port (ApplyWaterToActor)
void ApplyWaterToActor__FP3ALOT0(struct P *p,void *pwater)
{
 U origin,vel,pos,local,vFlow,v50,accel,bcast;
 float z,g;
 qword v,k;
 struct CLOCK *clock;
 if(p->state2DC==JUMP_STATE_RISE) goto vertical;
 switch(p->stateDF4) {
 case 7:
 vertical:
  origin.q=GetVel(p);
  if(origin.f[2]<0.0f) ApplyWaterToAlo__FP3ALOT0(p,pwater);
  break;
 case 3:case 10:
  if(!FWaterSurfaceUnder__FP5ACTORP3ALOP6VECTOR(p,pwater,&pos.q)) break;
  local.q=Mul(&p->m1B0,&p->v190);
  func_00228C18(pwater,pos.q,&vFlow.q,&v50.q);
  v=GetVel(p);
  vel.q=v;
  v=Add(v,local.q);
  v=Sub(v,vFlow.q);
  k=Broadcast(*(int *)&p->alpha10A4);
  bcast.q=k;
  v=Scale(v,k);
  accel.q=v;
  origin.q=PosOfLo__FP2LO(p);
  clock=&g_clock;
  GSmoothA(origin.f[2]+p->height10A0,vel.f[2]-vFlow.f[2],pos.f[2],clock->dt,&p->smp10A8,&z);
  g=(z-vel.f[2])/clock->dt-p->xE8->dvGravity.f[2];
  accel.f[2]=accel.f[2]>g?accel.f[2]:g;
  AccelAloPos__FP3ALOG9VU_VECTOR(p,accel.q);
  break;
 default:
  ApplyWaterToAlo__FP3ALOT0(p,pwater);
  break;
 }
}
