#include "vtbl.h"
struct LOV { char pad[0xC]; VTENT *pvt; };
/* a pursuit target record: its object and how its heading is taken (nMode) */
struct TARGETREC { char pad[0xC]; struct LOV *plo; int nMode; };
struct CM { char pad[0x60]; float xFwd; float yFwd; };
extern struct CM g_cm;
float atan2f(float y, float x);
#define VCALL31(o) ((float *(*)(void *))(o)->pvt[31].pfn)(VT_THIS((o), &(o)->pvt[31]))
/* RadTargetrec (0x20A690): the heading of a pursuit target record: by nMode 0 the camera's (its +0x60 row), 1 the
 * object's (the x row of its vt slot 31 matrix), -1 zero. */
// name: SafeHouse port (RadTargetrec)
float RadTargetrec__FP9TARGETREC(struct TARGETREC *ptargetrec)
{
    float rad = 0.0f;
    switch (ptargetrec->nMode) {
    case 0:
        rad = atan2f(g_cm.yFwd, g_cm.xFwd);
        break;
    case 1: {
        float *pmatA = VCALL31(ptargetrec->plo);
        float *pmatB = VCALL31(ptargetrec->plo);
        rad = atan2f(pmatA[1], pmatB[0]);
        break;
    }
    case -1:
        break;
    }
    return rad;
}
