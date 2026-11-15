/* STEP (class 51, derived from PO: a walking character; base of the guards and the player characters), partial
 * layout after the Sly 2 types in Lilly's ports. */
#ifndef STEP_H
#define STEP_H
#include "po.h"

typedef struct XP {
    /* 0x00 */ char unk_0x00[0x48];
    /* 0x48 */ struct SO *psoOther;    /* compared against an SO in SetStepOverlap__FP3ALOT0 */
} XP;

/* STEP::nMotion: what vt slot 70 (UpdateStepPhysMotion) does after gravity */
enum STEPMOTION {
    STEPMOTION_None = -1,
    STEPMOTION_Brake = 0,    /* brake the rotation toward vBrake in the heading frame */
    STEPMOTION_Target = 1    /* push the angular force toward posTarget */
};

typedef struct STEP {
    /* 0x000 */ PO po;
    /* 0x180 */ float uTurn;             /* gain of the turn toward the heading (field: SafeHouse port) */
    /* 0x184 */ int unk_0x184[3];
    /* 0x190 */ float vecVel[3];         /* velocity the feet push toward, in the heading's frame (field: SafeHouse port) */
    /* 0x19c */ int unk_0x19c;
    /* 0x1a0 */ float uGait;
    /* 0x1a4 */ int nMotion;             /* motion mode: STEPMOTION_* (field: SafeHouse port) */
    /* 0x1a8 */ float radHeading;        /* the heading (SetStepPhysHeading) (field: SafeHouse port) */
    /* 0x1ac */ int unk_0x1ac;
    /* 0x1b0 */ struct MATRIX3 matHeading; /* rotation about z by radHeading (field: SafeHouse port) */
    /* 0x1e0 */ qword posTarget;         /* STEPMOTION_Target's goal angular velocity (field: SafeHouse port) */
    /* 0x1f0 */ float gScale;            /* SetStepPhysScale (field: SafeHouse port) */
    /* 0x1f4 */ float vBrake[3];         /* STEPMOTION_Brake speeds (field: SafeHouse port) */
    /* 0x200 */ float uBrake;            /* scales vBrake x/y (field: SafeHouse port) */
    /* 0x204 */ int fNoContacts;         /* field: SafeHouse port */
    /* 0x208 */ XP *pxpFloor;          /* contact with the floor */
    /* 0x20c */ float tFloor;            /* when the floor contact was last there (field: SafeHouse port) */
    /* 0x210 */ float sFloorTarget;      /* the floor contact's target height (field: SafeHouse port) */
    /* 0x214 */ float sProbeDrop;        /* the second floor probe's depth below the first (-50 by default) */
    /* 0x218 */ qword *pposProbe0;      /* floor probe at the base: a point of the custom entry (field: SafeHouse port) */
    /* 0x21c */ qword *pposProbe1;      /* the probe sProbeDrop below it (field: SafeHouse port) */
    /* 0x220 */ float sSupport;          /* radius of the floor-support triangles around pposProbe0 (30) */
    /* 0x224 */ int unk_0x224[3];
    /* 0x230 */ qword posFloor;          /* world point of vecBase (field: SafeHouse port) */
    /* 0x240 */ qword vecBase;           /* the object's base in its own frame (field: SafeHouse port) */
    /* 0x250 */ int unk_0x250[2];
    /* 0x258 */ void *psoeCustom;        /* SOE: the custom entry carrying the floor probes (field: SafeHouse port) */
    /* 0x25c */ void *psoeOther;         /* SOE: the second mesh (SetStepMesh) (field: SafeHouse port) */
    /* 0x260 */ float sSize;             /* SetStepPhysSize (field: SafeHouse port) */
    /* 0x264 */ int oidMesh;             /* tag of the entry the custom entry is made from (field: SafeHouse port) */
    /* 0x268 */ void *psoeSource;        /* SOE: that entry (turned off) (field: SafeHouse port) */
    /* 0x26c */ char bhvstk[0x28];     /* BHVSTK: behaviour stack */
    /* 0x294 */ struct LO *ploPath;     /* own path object (cid 0x0A oid 713) (field: SafeHouse port) */
    /* 0x298 */ int nUnk298;
    /* 0x29c */ int unk_0x29c;
    /* 0x2a0 */ int acUnk2a0[6];        /* hold counts of the six effect SMs (vt slots 83 / 84) */
} STEP;

#endif
