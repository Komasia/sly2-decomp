/* GetSlyLaunchTarget: Sly's launch target dt seconds ahead: his position moved by his horizontal velocity (vt slot 33
 * without its z part) for dt, the direction that velocity, +0x4 / +0x8 150 / 75, kind 0. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct SLY { int pad[3]; VTENT *vt; };
struct LAUNCHTGT { int k; float g4; float g8; int pad; qword pos; qword dir; };   /* a launch target */
extern qword g_normalZ;
qword PosOfLo__FP2LO(struct SLY *psly);
// name: SafeHouse port (GetSlyLaunchTarget)
void GetSlyLaunchTarget__FP3SLYPvf(struct SLY *psly, struct LAUNCHTGT *ptgt, float dt)
{
    VTENT *e = &psly->vt[33];
    qword v, h, pos, s, r;
    VU u;
    v = ((qword (*)(void *))e->pfn)(VT_THIS(psly, e));
    {
        qword d, one, up = g_normalZ;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(up));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(up), "j"(d));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(h) : "j"(v), "j"(d));
    }
    pos = PosOfLo__FP2LO(psly);
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(dt));
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(pos), "j"(h), "j"(s));
    ptgt->dir = h;
    ptgt->g4 = 150.0f;
    ptgt->g8 = 75.0f;
    ptgt->pos = r;
    u.q = s;
    ptgt->k = 0;
}
