#include "vtbl.h"
struct VT;
/* the STEP fields used here */
struct STEP {
    char pad0[0xC]; struct VT *vt;
    char pad1[0x180 - 0x10]; float uTurn;
    char pad2[0x1A4 - 0x184]; int nMotion; float radHeading;
    char pad3[0x208 - 0x1AC]; int pxpFloor; float tFloor;
};
#define STEPMOTION_Brake 0
#define STEPMOTION_None -1
#define STEPMOTION_Target 1
struct VT { VTENT e[32]; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3C80[3];   /* turn gain polynomial in |heading error|: 1.5 - d */
extern float g_lmZeroOne[2];
void UpdateSo__FP2SOf(struct STEP *pstep);
void UpdateStepMesh__FP3ALO(struct STEP *pstep);
float atan2f(float y, float x);
float RadNormalize__Ff(float a);

/* UpdateStep (0x203FC0): STEP vt slot 16: the SO update, the mesh velocities (UpdateStepMesh), then the turn gain:
 * braking, from the heading error against the object's x row (vt slot 31), clamped to [0, 1]; otherwise 1. While
 * there is a floor contact tFloor tracks the clock. */
void UpdateStep__FP4STEPf(struct STEP *pstep)
{
    UpdateSo__FP2SOf(pstep);
    UpdateStepMesh__FP3ALO(pstep);
    switch (pstep->nMotion) {
    case STEPMOTION_Brake: {
        float *pmatA = ((float * (*)(void *))pstep->vt->e[31].pfn)(VT_THIS(pstep, &pstep->vt->e[31]));
        float *pmatB = ((float * (*)(void *))pstep->vt->e[31].pfn)(VT_THIS(pstep, &pstep->vt->e[31]));
        float drad = RadNormalize__Ff(pstep->radHeading - atan2f(pmatA[1], pmatB[0]));
        float u;
        drad = __builtin_fabsf(drad);
        u = D_002C3C80[0] + drad * (D_002C3C80[1] + drad * D_002C3C80[2]);
        {
            float lo = g_lmZeroOne[0], hi = g_lmZeroOne[1];
            if (u < lo)
                u = lo;
            else if (hi < u)
                u = hi;
        }
        pstep->uTurn = u;
        break;
    }
    case STEPMOTION_None:
    case STEPMOTION_Target:
        pstep->uTurn = 1.0f;
        break;
    }
    if (pstep->pxpFloor)
        pstep->tFloor = g_clock.t;
}
