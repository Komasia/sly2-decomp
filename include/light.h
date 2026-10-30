/* LIGHT (class 4, derived from ALO): partial layout used by the light.c functions around 0x1A3360. */
#ifndef LIGHT_H
#define LIGHT_H
#include "so.h"

typedef struct LIGHT {
    /* 0x000 */ ALO alo;
    /* 0x0e0 */ int nUnkE0;
    /* 0x0e4 */ int nStampXf;          /* XF::nStamp the light was last rebuilt for; -1 = never */
    /* 0x0e8 */ int unk_0xe8[2];
    /* 0x0f0 */ qword qwUnkF0;
    /* 0x100 */ char unk_0x100[0x18];
    /* 0x118 */ int nUnk118;
    /* 0x11c */ char unk_0x11c[0x34];
    /* 0x150 */ float gUnk150;
    /* 0x154 */ float gUnk154;         /* 240 after init */
    /* 0x158 */ int nUnk158;
    /* 0x15c */ int fUnk15c;           /* fUnk15c and fUnk160 exclude each other */
    /* 0x160 */ int fUnk160;
    /* 0x164 */ float gFalloffMin;     /* 200 after init */
    /* 0x168 */ float gFalloffMax;     /* 2000 after init */
} LIGHT;

void func_001A3968(LIGHT *plight);   /* rebuild the light's derived values (calls ConvertAngleStrength etc.) */
void func_001A3B38(LIGHT *plight);

#endif
