/* Sly 2 camera (CM, class 135, Sly 1 cm.c) and its camera policies (CPLCY family, Sly 1 cplcy.c).
 *
 * Layout and field names after Lilly's Sly 2 CM (src/hand/func_0014DC58.cpp, "ported from Lilly's personal Sly 2
 * decomp"), checked against the matched code: the CM constructor (func_0014D3D8) builds the policy members at
 * 0x3A0, 0x3B0, 0x450, 0x4A8, 0x4C0, 0x500, 0x520, 0x5F0 and 0x600 and the class is 0x630 bytes; SetCmNearClip /
 * SetCmFarClip / SetCmFov write sNearClip / sFarClip / fov+fovTarget+dfov; the fog setters write 0x240..0x24C.
 * The game's one camera object is D_002DDF40 (Lilly: g_cm).
 *
 * A camera policy is a g++ class whose data (CPLCYDATA) comes before its vtable pointer (+0x0C). Virtual slots
 * seen so far: 0 (all policies share func_0014FCC0), 1 (func_0014FCC8 in CPLCY), 2 (func_0014FCE8 in CPLCY: leave
 * the policy, restoring the near clip and target FOV kept in CPLCYDATA; it takes two more arguments), 5, 6 (CPLOOK / CPZOOM release their
 * sound references there).
 */
#ifndef CM_H
#define CM_H
#include "so.h"

typedef struct RGBA { uchar bRed, bGreen, bBlue, bAlpha; } RGBA;

typedef struct CPLCY {
    /* 0x00 */ void *pvHero;
    /* 0x04 */ float gFovTargetSaved;
    /* 0x08 */ float sNearClipSaved;
    /* 0x0c */ VTE *pvt;
} CPLCY;

typedef struct LM { float gMin, gMax; } LM;

typedef struct CPLOOK {
    /* 0x00 */ CPLCY cplcy;
    /* 0x10 */ float radPan;
    /* 0x14 */ float radTilt;
    /* 0x18 */ float swPan;
    /* 0x1c */ float swTilt;
    /* 0x20 */ float uZoom;
    /* 0x24 */ float svuZoom;
    /* 0x28 */ float rZoomMax;
    /* 0x2c */ float radFovZoom;
    /* 0x30 */ float radFovWide;
    /* 0x34 */ void *psndZoom;        /* CRefPtr<SND> */
    /* 0x38 */ void *psndUnk38;       /* CRefPtr<SND> */
    /* 0x3c */ LM lmPan;
    /* 0x44 */ LM lmTilt;
    /* 0x4c */ float radPanStart;
    /* 0x50 */ float radTiltStart;
    /* 0x54 */ int cEnter;
} CPLOOK;   /* 0x58 */

typedef struct CPZOOM {
    /* 0x00 */ CPLCY cplcy;
    /* 0x10 */ LO *ploOwner;
    /* 0x14 */ LO *ploFocus;
    /* 0x18 */ float uZoomTarget;
    /* 0x1c */ int unk_0x1c;
    /* 0x20 */ qword posFocusSmooth;
    /* 0x30 */ qword posEyeSmooth;
    /* 0x40 */ int fPose;
    /* 0x44 */ int unk_0x44[3];
    /* 0x50 */ qword pos;
    /* 0x60 */ qword eul;
    /* 0x70 */ float radFov;
    /* 0x74 */ int unk_0x74[3];
    /* 0x80 */ qword posTarget;
    /* 0x90 */ qword eulTarget;
    /* 0xa0 */ float radFovTarget;
    /* 0xa4 */ float radPan;
    /* 0xa8 */ float radTilt;
    /* 0xac */ float uZoom;
    /* 0xb0 */ float svuZoom;
    /* 0xb4 */ float rZoomMax;
    /* 0xb8 */ float radFovZoom;
    /* 0xbc */ float radFovWide;
    /* 0xc0 */ void *psndZoom;        /* CRefPtr<SND> */
    /* 0xc4 */ void *psndUnkc4;       /* CRefPtr<SND> */
    /* 0xc8 */ int unk_0xc8[2];
} CPZOOM;   /* 0xD0 */

typedef struct CPHANG {
    /* 0x00 */ CPLCY cplcy;
    /* 0x10 */ XF *pxfCam;
    /* 0x14 */ void *pact1;           /* ACT1 */
    /* 0x18 */ float tNext;
    /* 0x1c */ int unk_0x1c;
    /* 0x20 */ qword posSway;
    /* 0x30 */ qword vecVel;
} CPHANG;   /* 0x40 */

typedef struct CPTWOSHOT {
    /* 0x00 */ CPLCY cplcy;
    /* 0x10 */ LO *ploOwner;
    /* 0x14 */ LO *ploHero;
} CPTWOSHOT;

typedef struct CPR {
    /* 0x00 */ int cpp;
    /* 0x04 */ CPLCY *pcplcy;
    /* 0x08 */ SO *psoFocus;
    /* 0x0c */ void *pv;
} CPR;

typedef struct CPDEFI {
    /* 0x00 */ int grfcpd;
    /* 0x04 */ int unk_0x4[3];
    /* 0x10 */ qword posBase;
    /* 0x20 */ qword vBase;
    /* 0x30 */ float radHome;
    /* 0x34 */ float sAdjust;
    /* 0x38 */ float tMoveLast;
    /* 0x3c */ int nTurnAxis;
    /* 0x40 */ qword posAdjust;
} CPDEFI;

typedef struct CM {
    /* 0x000 */ BASIC basic;
    /* 0x010 */ void *pzonVis;           /* VISZONE */
    /* 0x014 */ uint grfvis;
    /* 0x018 */ float rFovCullRef;       /* set by SetCmMrdRatio */
    /* 0x01c */ float rCullScale;
    /* 0x020 */ float fov;
    /* 0x024 */ float fovTarget;
    /* 0x028 */ float dfov;
    /* 0x02c */ float rUnk2c, rUnk30, rUnk34, rUnk38;
    /* 0x03c */ float rAspect;
    /* 0x040 */ float gTanHalfX;
    /* 0x044 */ float gTanHalfY;
    /* 0x048 */ float sNearCorner;
    /* 0x04c */ float sNearClip;
    /* 0x050 */ float sFarClip;
    /* 0x054 */ int unk_0x54[3];
    /* 0x060 */ qword amat[4];           /* MATRIX4: rotation rows, then the position */
    /* 0x0a0 */ float agFrustumXyz[12];
    /* 0x0d0 */ float agFrustumWideXyz[12];
    /* 0x100 */ struct MATRIX4 matProj;
    /* 0x140 */ struct MATRIX4 matViewProj;
    /* 0x180 */ struct MATRIX4 matViewProjInv;
    /* 0x1c0 */ qword aplaneFrustum[4];
    /* 0x200 */ qword aplaneFrustumWide[4];
    /* 0x240 */ float sNearFog;
    /* 0x244 */ float sFarFog;
    /* 0x248 */ float uFogMax;
    /* 0x24c */ RGBA rgbaFog;
    /* 0x250 */ float agRecipFit[4];
    /* 0x260 */ SO *psoAdjust;
    /* 0x264 */ int unk_0x264[3];
    /* 0x270 */ CPDEFI cpdefi;
    /* 0x2c0 */ qword dposAdjust;
    /* 0x2d0 */ float vAdjust[3];
    /* 0x2dc */ int unk_0x2dc;
    /* 0x2e0 */ qword dposFocus;
    /* 0x2f0 */ float vFocus[3];
    /* 0x2fc */ int unk_0x2fc;
    /* 0x300 */ int nCut;
    /* 0x304 */ float radCutPan;
    /* 0x308 */ float radCutTilt;
    /* 0x30c */ int cmodeHero;
    /* 0x310 */ CPR acpr[8];             /* policy stack; acpr[0] is the active one */
    /* 0x390 */ float tModeStart;
    /* 0x394 */ int unk_0x394[3];
    /* 0x3a0 */ CPLCY part3a0;           /* CMPART1 */
    /* 0x3b0 */ char part3b0[0xa0];      /* CMPART2 (tunnel-following policy) */
    /* 0x450 */ CPLOOK cplook;
    /* 0x4a8 */ char part4a8[0x18];      /* CPCAMERA */
    /* 0x4c0 */ CPHANG part4c0;
    /* 0x500 */ char part500[0x20];      /* CPCAMBLEND */
    /* 0x520 */ CPZOOM cpzoom;
    /* 0x5f0 */ CPLCY part5f0;           /* CPTURRET */
    /* 0x600 */ CPTWOSHOT part600;
    /* 0x618 */ float tJolt;
    /* 0x61c */ int nUnk61c;
    /* 0x620 */ float rUnk620;
    /* 0x624 */ float rUnk624;
} CM;   /* 0x630 */

extern CM D_002DDF40;   /* the camera (Lilly: g_cm) */

void RecalcCmFrustrum__FP2CM(CM *pcm);
void SetCmFov__FP2CMf(CM *pcm, float fov);
void SetCmNearClip__FP2CMf(CM *pcm, float sNearClip);
void SetCmFarClip__FP2CMf(CM *pcm, float sFarClip);

#endif
