/* ComputeLight (0x1A3968): rebuilds a light's record (+0x120) and its light-context selection data (+0x100 / +0x110 /
 * +0x114) from its options: the angular falloff from the angle (at least 30) and the brightness (max of strength and
 * the colour's value) by ConvertAngleStrength; the colour (HSV -> RGB, then 0x1ED2D8's adjustment) and the strength
 * divided by the brightness; directional (kind 0): the direction is the world matrix's first row (vtable slot 31);
 * point (kind 1): the position, with the distance falloff fitted from sNear (1) to sFar (0). Then func_001A3B38.
 * Field names: include/light.h, SafeHouse lightsw.cpp LIGHTREC / LIGHTSEL. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z; } V3;
struct LIGHT;
struct LIGHT {
    int x0, x4, x8;
    VTENT *vt;
    char pad10[0xE0 - 0x10];
    int kind;            /* 0 directional, 1 point */
    char padE4[0xF0 - 0xE4];
    char hsv[8];
    float hsvValue;      /* hsv[2] */
    int xFC;
    union { qword q; struct { float x, y, z, w; } f; } posSel;   /* the selection: the light's position (point) */
    float gSelConst, gSelSlope;   /* the selection's brightness by distance: const + slope d */
    int pad118[2];
    int kindRec;          /* the record (+0x120): its kind */
    float angularOffset, angularScale, distanceOffset;
    float r, g, b, a;     /* the colour and strength over the brightness */
    V3 dirOrPos;
    float distanceScale, strength, angle;
    int pad158[3];
    float sNear, sFar;
};
void ConvertAngleStrength(float a, float b, float c, float d, float *pa, float *pb) asm("ConvertAngleStrength__FffffPfT4");
void ConvertUserHsvToUserRgb(void *p, V3 *pv) asm("ConvertUserHsvToUserRgb__FP6VECTORT0");
void func_001ED2D8(V3 *pv);
qword PosOfLo__FP2LO(struct LIGHT *p);
void FitLinearFunction__FffffPfT4(float a, float b, float c, float d, float *pa, float *pb);
void func_001A3B38(struct LIGHT *p);
static inline float Max1(float a, float b) { return (a > b) ? a : b; }
#define VT_MAT_WORLD 31
// name: SafeHouse port (ComputeLight)
void ComputeLight__FP11LIGHTPARAMS(struct LIGHT *plight)
{
    V3 rgb;
    float gBright;
    float deg;
    gBright = Max1(plight->strength, plight->hsvValue);
    deg = (plight->angle > 30.0f) ? plight->angle : 30.0f;
    ConvertAngleStrength(deg, 0.0f, 0.0f, gBright, &plight->angularOffset, &plight->angularScale);
    ConvertUserHsvToUserRgb(plight->hsv, &rgb);
    func_001ED2D8(&rgb);
    plight->r = rgb.x;
    plight->g = rgb.y;
    plight->b = rgb.z;
    plight->a = plight->strength;
    if (0.0f < gBright) {
        plight->r = plight->r / gBright;
        plight->g = plight->g / gBright;
        plight->b = plight->b / gBright;
        plight->a = plight->a / gBright;
    }
    plight->angularScale = -plight->angularScale;
    switch (plight->kindRec = plight->kind) {
    case 0:
        {
            struct F4 { float x, y, z, w; } *pv = (struct F4 *)&plight->posSel;
            pv->z = 0.0f;
            pv->y = 0.0f;
            pv->x = 0.0f;
        }
        plight->gSelConst = 1.0f;
        plight->gSelSlope = 0.0f;
        plight->dirOrPos = *((V3 * (*)(struct LIGHT *))plight->vt[VT_MAT_WORLD].pfn)((struct LIGHT *)VT_THIS(plight, &plight->vt[VT_MAT_WORLD]));
        break;
    case 1:
        plight->posSel.q = PosOfLo__FP2LO(plight);
        plight->dirOrPos = *(V3 *)&plight->posSel;
        FitLinearFunction__FffffPfT4(plight->sNear, 1.0f, plight->sFar, 0.0f, &plight->distanceOffset, &plight->distanceScale);
        plight->gSelConst = plight->distanceOffset;
        plight->gSelSlope = plight->distanceScale;
        break;
    }
    gBright = Max1(plight->hsvValue, plight->strength);
    plight->gSelConst = plight->gSelConst * gBright;
    plight->gSelSlope = plight->gSelSlope * gBright;
    func_001A3B38(plight);
}
