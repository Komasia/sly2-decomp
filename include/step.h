/* STEP (class 51, derived from PO: a walking character; base of the guards and the player characters), partial
 * layout after the Sly 2 types in Lilly's ports. */
#ifndef STEP_H
#define STEP_H
#include "po.h"

typedef struct XP {
    /* 0x00 */ char unk_0x00[0x48];
    /* 0x48 */ struct SO *psoOther;    /* compared against an SO in func_00204C60 */
} XP;

typedef struct STEP {
    /* 0x000 */ PO po;
    /* 0x180 */ float gUnk180;
    /* 0x184 */ int unk_0x184[3];
    /* 0x190 */ float vUnk190[3];
    /* 0x19c */ int unk_0x19c;
    /* 0x1a0 */ float uGait;
    /* 0x1a4 */ int nUnk1a4;
    /* 0x1a8 */ float radTarget;
    /* 0x1ac */ int unk_0x1ac;
    /* 0x1b0 */ struct MATRIX3 matTarget;
    /* 0x1e0 */ qword qwUnk1e0;
    /* 0x1f0 */ float rSpin;
    /* 0x1f4 */ float vSpin[3];
    /* 0x200 */ float rUnk200;
    /* 0x204 */ int nUnk204;
    /* 0x208 */ XP *pxpFloor;          /* contact with the floor */
    /* 0x20c */ float tUnk20c;
    /* 0x210 */ float gUnk210;
    /* 0x214 */ float gUnk214;
    /* 0x218 */ qword *pqwUnk218;
    /* 0x21c */ qword *pqwUnk21c;
    /* 0x220 */ float gUnk220;
    /* 0x224 */ int unk_0x224[3];
    /* 0x230 */ qword qwUnk230;
    /* 0x240 */ qword qwUnk240;
    /* 0x250 */ int unk_0x250[2];
    /* 0x258 */ void *ppartUnk258;
    /* 0x25c */ int unk_0x25c;
    /* 0x260 */ float rUnk260;
    /* 0x264 */ int idUnk264;
    /* 0x268 */ void *precUnk268;
    /* 0x26c */ char bhvstk[0x28];     /* BHVSTK: behaviour stack */
    /* 0x294 */ void *pvUnk294;
    /* 0x298 */ int nUnk298;
    /* 0x29c */ int unk_0x29c;
    /* 0x2a0 */ int acUnk2a0[6];
} STEP;

#endif
