/* FActorPoseDone: whether the actor's pose interaction (state 5, with +0x4D4) is done: its object near (5 units) the
 * point its pose gives (vt slot 32, in world space), and for kind 1 (+0x9A4) its animation's time reached. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct BUF { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; VTENT *vt; };
struct ASEGA { char pad[0x1C]; float t; };
struct ACTOR {
    char pad[0x4C8]; int n4C8; char pad1[0x4D4 - 0x4CC]; int n4D4; char pad2[0x934 - 0x4D8]; struct LO *ploPose;
    char pad3[0x994 - 0x938]; struct ASEGA *pasega994; char pad4[0x9A4 - 0x998]; int n9A4;
};
#include "clock.h"
void func_002309E8(void *a, int b, M4 *pm, int c, float g);
qword PosOfLo__FP2LO(void *pactor);
static __inline__ qword Mul(M4 *pm, qword v)
{
    qword o;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(o) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return o;
}
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
// name: SafeHouse port (FActorPoseDone)
int FActorPoseDone__FP5ACTOR(struct ACTOR *pactor)
{
    struct BUF buf;
    M4 m;
    qword v;
    if (pactor->n4C8 != 5 || !pactor->n4D4) return 1;
    func_002309E8(((void * (*)(void *, struct BUF *))pactor->ploPose->vt[32].pfn)(VT_THIS(pactor->ploPose, &pactor->ploPose->vt[32]), &buf), 0, &m, 0, 0.0f);
    v = Mul(&m, buf.pos);
    if (5.0f < GDist(PosOfLo__FP2LO(pactor->ploPose), v)) return 0;
    if (pactor->n9A4 != 1) return 1;
    if (g_clock.t < pactor->pasega994->t) return 0;
    return 1;
}
