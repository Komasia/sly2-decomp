/* LaunchActorTo: the actor flies to posTarget in tFlight: the ballistic velocity from its position (raised by +0x248)
 * under its gravity (vt slot 35); unless hurt, the jump takes kind 8 with that velocity (horizontal) and g2F4 (+0x2F4).
 * SafeHouse port (actor.cpp). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct PHYS { char pad[0x80]; qword vecGravity; };   /* +0x80: the acceleration of gravity */
struct ACTOR {
    char pad0[0xC]; VTENT *vt; char pad1[0xE8 - 0x10]; struct PHYS *pphys;
    char pad2[0x248 - 0xEC]; float dz; char pad3[0x2E8 - 0x24C]; int f2E8; int f2EC; char pad4[0x2F4 - 0x2F0];
    float g2F4; char pad5[0x300 - 0x2F8]; int kJump300; char pad6[0x360 - 0x304]; UQ v360;
    char pad7[0xDF4 - 0x370]; int xDF4;
};
qword PosOfLo__FP2LO(struct ACTOR *pactor);
qword VecBallisticVelocity__FfG9VU_VECTORN21(qword a, qword b, float tFlight, qword c);
void SetJumpKind__FP4JUMPiiP2LO(void *pactor, int a, int b, int c);
// name: SafeHouse port (LaunchActorTo)
void LaunchActorTo__FP5ACTORG9VU_VECTORff(struct ACTOR *pactor, qword posTarget, float tFlight, float g2F4)
{
    UQ pos;
    UQ vel;
    pos.q = PosOfLo__FP2LO(pactor);
    pos.f[2] += pactor->dz;
    vel.q = VecBallisticVelocity__FfG9VU_VECTORN21(pos.q, posTarget, tFlight, pactor->pphys->vecGravity);
    ((void (*)(void *, qword))pactor->vt[35].pfn)(VT_THIS(pactor, &pactor->vt[35]), vel.q);
    if (pactor->xDF4 == -1) {
        SetJumpKind__FP4JUMPiiP2LO((char *)pactor + 0x2C0, 8, 0, 0);
        pactor->kJump300 = 3;
        pactor->v360.q = vel.q;
        pactor->v360.f[2] = 0.0f;
        pactor->g2F4 = g2F4;
        if (g2F4 == pactor->v360.f[2]) {
            pactor->f2E8 = 0;
            pactor->f2EC = 0;
        }
    }
}
