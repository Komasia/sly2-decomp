/* FActorBelowFloorSoon: whether within dt the actor's height over the floor (+0x248, with its vertical velocity and
 * gravity) drops to 0 and the ground there would catch it (FDropOnGround). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
struct SO;
struct PHYS { char pad[0x88]; float zGravity; };
struct SO { int x0, x4, x8; VTENT *vt; char pad[0xE8 - 0x10]; struct PHYS *pphys; char pad2[0x248 - 0xEC]; float zAboveFloor; };
qword PosOfLo__FP2LO(struct SO *pactor);
int FDropOnGround__FP6VECTORffiPv(qword *ppos, int a, int b, float f, float g);
// name: SafeHouse port (FActorBelowFloorSoon)
int FActorBelowFloorSoon__FP5ACTORf(struct SO *pactor, float dt)
{
    union { qword q; float f[4]; } pos;
    float z = pactor->zAboveFloor;
    z += dt * GetZ(((qword (*)(struct SO *))pactor->vt[33].pfn)((struct SO *)VT_THIS(pactor, &pactor->vt[33])));
    z += 0.5f * dt * dt * pactor->pphys->zGravity;
    if (z > 0.0f)
        return 0;
    pos.q = PosOfLo__FP2LO(pactor);
    return FDropOnGround__FP6VECTORffiPv(&pos.q, 0, 0, 0.0f, z);
}
