#include "stepguard.h"
typedef union { qword q; float f; } U;
struct ASEGA { char pad[0x1C]; float dtStep; };
struct SMA { char pad[0x10]; qword vel; char pad2[0x30 - 0x20]; struct ASEGA *pasega; };
struct K2PLAY { char pad[0x10]; int st; char pad2[0x38 - 0x14]; struct ASEGA *pasega; };
struct KINDE { int k; int oid; void *pvState; };
union FLOATWORD { float g; int bits; };
struct CTRLPOS { int pad[2]; union FLOATWORD *pfScale; };
extern qword D_002A2DD0;
qword VelActorAnimRoot__FP5ACTORPvf(struct GUARD *, struct ASEGA *, float);
qword func_00204ED8(struct GUARD *, struct ASEGA *, float);
void UpdateK2__FP6K2PLAY(struct K2PLAY *);
/* SteerByKinde (0x209618): steers the guard by what plays a kind entry: the root velocity (and, for an ASEG / SM, the
 * kind-6 root velocity, into STEP::posTarget) of its ASEGA, of the KIND2 player's while not in the air, or the KIND3
 * player's chosen velocity; scaled by the guard's scale controller, negated into STEP::vecVel. Field names:
 * SafeHouse port. */
// name: SafeHouse port (SteerByKinde)
void SteerByKinde__FP5KINDEP5GUARD(struct KINDE *pkinde, struct GUARD *pguard)
{
    U factor, vel;
    register qword scalar __asm__("vf1");
    qword extra;
    register qword neg __asm__("vf2");
    {register qword *zeroAddress __asm__("v0")=&D_002A2DD0;
     register qword zero __asm__("v0");
     __asm__("lq %0,0(%1)":"=r"(zero):"r"(zeroAddress),"m"(*zeroAddress));
     __asm__("sq %1,%0":"=m"(vel.q):"r"(zero));}
    extra=vel.q;
    { register int k __asm__("v1");
      __asm__("lw %0,%1":"=r"(k):"m"(pkinde->k));
    switch (k) {
    case 0:
    case 1:
        {
            struct ASEGA *pasega;
            if (k == 0) pasega = (struct ASEGA *)pkinde->pvState;
            else pasega = ((struct SMA *)pkinde->pvState)->pasega;
            if (pasega) {
                vel.q = VelActorAnimRoot__FP5ACTORPvf(pguard, pasega, pasega->dtStep);
                extra = func_00204ED8(pguard, pasega, pasega->dtStep);
            }
        }
        break;
    case 2:
        {
            struct K2PLAY *pk2play;
            UpdateK2__FP6K2PLAY((struct K2PLAY *)pkinde->pvState);
            pk2play = (struct K2PLAY *)pkinde->pvState;
            if (pk2play->st > 0 && (pk2play->st < 3 || pk2play->st == 4)) break;
            vel.q = VelActorAnimRoot__FP5ACTORPvf(pguard, pk2play->pasega, pk2play->pasega->dtStep);
        }
        break;
    case 3: {
        register struct SMA *pvState __asm__("v0")=(struct SMA *)pkinde->pvState;
        register qword vector __asm__("v0");
        __asm__("lq %0,16(%1)":"=r"(vector):"r"(pvState),"m"(pvState->vel));
        vel.q=vector; }
        break;
    }
    }
    {
      register qword current __asm__("vf2")=vel.q;
      if (pguard->pscale) {
        register union FLOATWORD *wordAddress __asm__("v0")=pguard->pscale->pfScale;
        register int parameterWord __asm__("v0");
        __asm__("lw %0,0(%2)\n\tqmtc2.ni %0,%1":"=r"(parameterWord),"=j"(scalar):"r"(wordAddress),"m"(wordAddress->bits));
        factor.q=scalar;
        __asm__("vmulx.xyzw %0,%0,%1x":"+j"(current):"j"(factor.q));
        vel.q=current;
      }
    }
    pguard->step.posTarget = extra;
    __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(scalar) : "r"(-1.0f));
    factor.q=scalar;
    { register qword source __asm__("vf3")=vel.q;
      __asm__("vmulx.xyzw %0,%1,%2x":"=j"(neg):"j"(source),"j"(factor.q)); }
    *(qword *)pguard->step.vecVel = neg;   /* STEP::vecVel as a quadword */
}
