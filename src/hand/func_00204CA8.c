#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
/* the rotation record (SO +0x5C): its angular velocity */
struct XFROT { char pad[0xB0]; qword dwAngular; };
struct ACTOR { char pad[0xC]; VTENT *pvt; char pad2[0x5C - 0x10]; struct XFROT *pxfRot; char pad3[0x1A8 - 0x60]; float radHeading; char pad4[0x1F4 - 0x1AC]; int smpTurn; };
float atan2f(float y, float smpTurn);
void RadSmooth(float radCur, float radTarget, float dt, int *psmp, float *pdradNext) asm("RadSmooth__FfffP3SMPPf");
/* TurnActorNow (0x204CA8): sets the actor's angular velocity z at once to the smoothed turn from its current heading
 * (the x row of vt slot 31's matrix) toward radHeading, then hands it to vt slot 36 (set angular velocity). */
// name: SafeHouse port (TurnActorNow)
void TurnActorNow__FP5ACTOR(struct ACTOR *pactor)
{
    U dw;
    float *pmatA, *pmatB;
    dw.q = pactor->pxfRot->dwAngular;
    pmatA = ((float *(*)(void *))pactor->pvt[31].pfn)(VT_THIS(pactor, &pactor->pvt[31]));
    pmatB = ((float *(*)(void *))pactor->pvt[31].pfn)(VT_THIS(pactor, &pactor->pvt[31]));
    RadSmooth(atan2f(pmatA[1], pmatB[0]), pactor->radHeading, 0.0f, &pactor->smpTurn, &dw.f[2]);
    ((void (*)(void *, qword))pactor->pvt[36].pfn)(VT_THIS(pactor, &pactor->pvt[36]), dw.q);
}
