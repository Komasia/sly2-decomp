/* UpdateDamageMotion (0x1A1148): the actor's motion during damage reactions (DAMAGE +0x4): in 1 / 2 the gravity is
 * cancelled and the velocity damped to rest (AccelAloTowardPosition with the CLQ D_002BFA90); in 5 / 11 the same, but
 * the clip's vertical motion (+0x198, the root velocity's z) is kept. SafeHouse damage.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct SOST { char pad[0x80]; qword dvGravity; };  /* the object's physics state: +0x80 its gravity */
struct O { char pad[0xC]; VTENT *vt; char pad1[0xE8-0x10]; struct SOST *xE8; char pad2[0x198-0xEC]; float f198; void Set(qword v) __asm__("AccelAloPos__FP3ALOG9VU_VECTOR"); void Negate(U &u); };
struct DAMAGE { struct O *pactor; int nState; };  /* ACTOR +0xDF0 */
extern "C" qword g_vecZero asm("D_002A2DD0");
extern "C" float g_clqDamageDamp[] asm("D_002BFA90");  /* CLQ {0, 10, 0.01, 0} */
#include "clock.h"

extern "C" void AccelAloTowardPosition(struct O *p,qword a,int n,qword b,float *c) asm("AccelAloTowardPosition__FP3ALOG9VU_VECTORP3CLQT1T2");
static inline qword Broadcast(float g) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g));return q; }
static inline qword BroadcastTo(float g,U *u) { qword q=Broadcast(g); u->q=q;return q; }
static inline qword Scale(qword a,qword b) { qword q; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(q) : "j"(a),"j"(b));return q; }
static inline float GetZ(qword v) { float g; __asm__("pextuw %0,$0,%1" : "=r"(g) : "r"(v));return g; }
inline void O::Negate(U &u) { qword v=xE8->dvGravity; qword k=Broadcast(-1.0f); u.q=k; Set(Scale(v,k)); }
// name: SafeHouse port (UpdateDamageMotion)
extern "C" void UpdateDamageMotion__FP5ACTOR(struct DAMAGE *pdmg)
{
 U u,vel,u2;
 qword k;
 float zero;
 switch(pdmg->nState) {
 case 1:case 2:
  pdmg->pactor->Negate(u);
  AccelAloTowardPosition(pdmg->pactor,g_vecZero,0,g_vecZero,g_clqDamageDamp);
  break;
 case 5:case 11:
  pdmg->pactor->Negate(u2);
  vel.i[2]=0;vel.i[1]=0;vel.i[0]=0;
  zero=vel.f[2];
  if(pdmg->pactor->f198!=zero)
   vel.f[2]=GetZ(((qword (*)(void *))pdmg->pactor->vt[33].pfn)(VT_THIS(pdmg->pactor, &pdmg->pactor->vt[33])));
  AccelAloTowardPosition(pdmg->pactor,g_vecZero,0,vel.q,g_clqDamageDamp);
  if(pdmg->pactor->f198!=zero) {
   u.f[2]=zero;u.f[1]=zero;u.f[0]=zero;
   u.f[2]=(-pdmg->pactor->f198-vel.f[2])/g_clock.dt;
   pdmg->pactor->Set(u.q);
  }
  break;
 }
}
