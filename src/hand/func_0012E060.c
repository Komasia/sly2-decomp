/* The target controller's (kind 8, CTRLTARGET) Query: the value / velocity it drives the record toward t seconds
 * on: the target itself once the arrival time (XF +0xA8) is reached, else the Hermite from the record's current
 * position / velocity to the target over the time left. Layout: SafeHouse port (xf.h CTRLTARGET, lo.h XF). */
typedef int qword __attribute__((mode(TI)));
#include "clock.h"
typedef struct XF {
    char pad[0x30]; qword pos;            /* the local matrix's translation row */
    char pad2[0x68]; float tTarget;       /* +0xA8; field: SafeHouse port */
    char pad3[4]; qword vel;              /* +0xB0; field: SafeHouse port */
} XF;
typedef struct CTRLTARGET { char pad[8]; XF *pxf; char pad2[0x14]; qword pos; qword vel; } CTRLTARGET;   /* field: SafeHouse port */
void Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *ppos, qword *pv, int n);
void func_0012E060(CTRLTARGET *pctrl, qword *ppos, qword *pvel, float t)
{
    float tNow = g_clock.t;
    XF *pxf = pctrl->pxf;
    if (pxf->tTarget <= tNow + t) {
        if (ppos) *ppos = pctrl->pos;
        if (pvel) *pvel = pctrl->vel;
    } else {
        Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(pxf->tTarget - tNow, t, 1.0f, pxf->pos, pxf->vel, pctrl->pos, pctrl->vel, ppos, pvel, 0);
    }
}
