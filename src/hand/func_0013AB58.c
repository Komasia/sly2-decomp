/* UpdateBomb: the SO update; the flight ends when its end time has passed or its speed (vt slot 33's velocity) falls
 * under svMin; otherwise a projectile with sweep entries sweeps. Layout: SafeHouse port (projectile.cpp). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct BOMB { char pad[0xC]; VTENT *pvt; char pad2[0x154 - 0x10]; float tEnd; float svMin; char pad3[0x1F4 - 0x15C]; int csweep; };
#include "clock.h"
void UpdateSo__FP2SOf(struct BOMB *pbomb);
void EndProjectile__FP3ALO(struct BOMB *pbomb);
void SweepProjectile__FP3ALO(struct BOMB *pbomb);
static __inline__ float GLength(qword v)
{
    qword d, t;
    float g;
    __asm__("vmul.xyz %0, %1, %1\n"
        "vaddw.x %2, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %2, %0z" : "=j"(d), "+j"(v), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
void UpdateBomb__FP4BOMBf(struct BOMB *pbomb)
{
    UpdateSo__FP2SOf(pbomb);
    if (pbomb->tEnd <= g_clock.t)
        goto out;
    {
        VTENT *vt = pbomb->pvt;
        qword v = ((qword (*)(void *))vt[33].pfn)(VT_THIS(pbomb, &vt[33]));
        int fSlow = GLength(v) < pbomb->svMin;
        if (fSlow) {
        out:
            EndProjectile__FP3ALO(pbomb);
        } else if (pbomb->csweep) {
            SweepProjectile__FP3ALO(pbomb);
        }
    }
}
