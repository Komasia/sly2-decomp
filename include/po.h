/* PO (class 50, derived from SO: a player-controllable object) and its controller POCTL; partial layouts after
 * the Sly 2 types in Lilly's ports. SW is the world; only the fields used here. */
#ifndef PO_H
#define PO_H
#include "so.h"

typedef struct POCTL {
    /* 0x00 */ BASIC basic;
    /* 0x10 */ float dxLeft, dyLeft, radLeft, sLeft;
    /* 0x20 */ float dxRight, dyRight, radRight, sRight;
    /* 0x30 */ uint grfbtn;            /* buttons held */
    /* 0x34 */ int unk_0x34[3];
    /* 0x40 */ struct MATRIX3 matPanTilt;
    /* 0x70 */ float sLeftHold;
    /* 0x74 */ float sRightHold;
    /* 0x78 */ int grfPressed;
    /* 0x7c */ struct PO *ppo;
    /* 0x80 */ int nState;
} POCTL;

typedef struct PO {
    /* 0x000 */ SO so;
    /* 0x150 */ POCTL *pctl;
    /* 0x154 */ uint grfbtnForce;
    /* 0x158 */ int unk_0x158[4];
    /* 0x168 */ struct PO *ppoUnk168;  /* a clone points it at itself (ClonePo) */
    /* 0x16c */ void *ptnCam;          /* camera tunnel (TN) used while this PO is in focus */
    /* 0x170 */ int unk_0x170[4];
} PO;   /* 0x180 bytes */

/* the world: current player and the PO currently overriding it */
typedef struct SW {
    /* 0x0000 */ char unk_0x0000[0x3EFC];
    /* 0x3efc */ PO *ppoCur;
    /* 0x3f00 */ PO *ppoOverride;
} SW;

extern SW D_003DD490;   /* the world */

#endif
