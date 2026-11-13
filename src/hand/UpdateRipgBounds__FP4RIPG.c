/* UpdateRipgBounds (class 0x57 vt slot 49): the attachment's box restored from the object's saved one (+0x170 lo,
 * +0x180 hi, +0x190 center, +0x1A0 radius) into its bounds record (+0xEC); the bounds are marked changed
 * (D_003E115C) and the object's overlap marked clean. Fields: SafeHouse port (physcheck.cpp). */
#include "vec.h"

struct BOUNDS {
    /* 0x00 */ struct VECTOR4 posMin;
    /* 0x10 */ struct VECTOR4 posMax;
    /* 0x20 */ struct VECTOR4 posCenter;
    /* 0x30 */ float sRadius;
};
struct RIPG {
    /* 0x000 */ char pad0[0xec];
    /* 0x0ec */ struct BOUNDS *pbounds;
    /* 0x0f0 */ char padf0[0x170 - 0xf0];
    /* 0x170 */ struct VECTOR4 posMin;
    /* 0x180 */ struct VECTOR4 posMax;
    /* 0x190 */ struct VECTOR4 posCenter;
    /* 0x1a0 */ float sRadius;
};
extern int D_003E115C;   /* the bounds changed */
void UnmarkOxaDirty1(struct RIPG *pripg) asm("UnmarkOxaDirty1__FP3ALO");

void UpdateRipgBounds__FP4RIPG(struct RIPG *pripg)
{
    pripg->pbounds->posMin = pripg->posMin;
    pripg->pbounds->posMax = pripg->posMax;
    pripg->pbounds->posCenter = pripg->posCenter;
    pripg->pbounds->sRadius = pripg->sRadius;
    D_003E115C = 1;
    UnmarkOxaDirty1(pripg);
}
