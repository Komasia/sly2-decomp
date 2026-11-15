/* LIGHT (class 4, derived from XFM): partial layout used by the light.c functions around 0x1A3360 (module
 * 0x1A3260..0x1A4E08, Sly 1 light.c). Field names: SafeHouse port (lightsw.h LIGHTPARAMS, the loaded options
 * EOPIDs 151..158 of class 4). */
#ifndef LIGHT_H
#define LIGHT_H
#include "so.h"

typedef struct LIGHT {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int kind;               /* field: SafeHouse port (EOPID 151) - 0 directional, 1 point */
    /* 0x0e4 */ int nStampXf;          /* XF::nStamp the light was last rebuilt for; -1 = never */
    /* 0x0e8 */ int unk_0xe8[2];
    /* 0x0f0 */ qword hsv;              /* field: SafeHouse port (152) - hue 0..360, saturation and value 0..255 */
    /* 0x100 */ char unk_0x100[0x18];   /* the light context's selection data (+0x100 / +0x110 / +0x114) */
    /* 0x118 */ int nUnk118;
    /* 0x11c */ char unk_0x11c[0x34];
    /* 0x150 */ float strength;         /* field: SafeHouse port (153) */
    /* 0x154 */ float angle;            /* field: SafeHouse port (154) - degrees, 240 after init */
    /* 0x158 */ int fShadow;            /* field: SafeHouse port (156, n158) - casts the shadow direction (0x1A4478) */
    /* 0x15c */ int fNoContext;         /* field: SafeHouse port (157) - not a light-context candidate; excludes fNoBake */
    /* 0x160 */ int fNoBake;            /* field: SafeHouse port (158) - not baked, not the world's light */
    /* 0x164 */ float gFalloffMin;     /* field: SafeHouse port (155, sNear) - point falloff, 200 after init */
    /* 0x168 */ float gFalloffMax;     /* field: SafeHouse port (155, sFar) - 2000 after init */
} LIGHT;

void ComputeLight__FP11LIGHTPARAMS(LIGHT *plight);   /* rebuild the light's derived values (calls ConvertAngleStrength etc.) */
void func_001A3B38(LIGHT *plight);

#endif
