/* Sly 2 ACTOR layout (partial), for C and C++ sources.
 *
 * ACTOR (class id 0x34) derives from SO. Field offsets and names come from SafeHouse (FridiNaTor1's PC port,
 * Sly2-Release/actor.h and interact.h, "+0x..." offset comments; credited in CREDITS.md) and the matched code that
 * reads them. Only fields whose offsets the matched sources use are named; the spans between are unk_0xXXX padding.
 * The sub-objects (JUMP at +0x2C0, INTERACT at +0x4C0) keep SafeHouse's names where they are known.
 * ACTOR derives SO -> PO -> STEP -> ACTOR (classes.tsv; SafeHouse calls these ALO / SO / PO / PLAYER). The PO and
 * STEP fields (0x150..0x2C0) are repeated here as named fields at the same offsets (po.h / step.h names) rather than
 * an embedded STEP, so that the actor.h users' access paths (pactor->so....) stay as they are.
 */
#ifndef ACTOR_H
#define ACTOR_H
#include "so.h"

struct ALO;
struct ACTOR;
struct ASEGA;
struct POCTL;
struct PO;
struct XP;
struct PHOTOPROMPT;
struct ASEG;

/* the jump (ACTOR +0x2C0; SafeHouse actor.h JUMP) */
typedef struct JUMP {
    /* 0x000 */ struct ACTOR *pactor;
    /* 0x004 */ int kind;               /* the jump's kind (0..18) */
    /* 0x008 */ int n8;
    /* 0x00c */ struct ALO *ploC;       /* the animation state's object */
    /* 0x010 */ float g10;
    /* 0x014 */ float s14;
    /* 0x018 */ float t18;              /* the kind's start */
    /* 0x01c */ int state;              /* the animation state (-1 none, 0..22) */
    /* 0x020 */ float t20;              /* its start */
    /* 0x024 */ char unk_0x024[0x200 - 0x24];
} JUMP;

/* the reach toward an object (INTERACT +0x440, kinds 5 / 9; SafeHouse reach.h REACH) */
typedef struct REACH {
    /* 0x00 */ char unk_0x00[0x34];
    /* 0x34 */ struct LO *ploEnd;       /* the end object (AttachReachObject) */
    /* 0x38 */ char unk_0x38[0xbc - 0x38];
} REACH;

/* the interaction (ACTOR +0x4C0; SafeHouse interact.h INTERACT): what a player does with an object it holds on to
 * or uses */
typedef struct INTERACT {
    /* 0x000 */ struct ACTOR *pactor;
    /* 0x004 */ float tBegin;           /* the action's start */
    /* 0x008 */ int kind;               /* the running interaction's kind (-1 none) */
    /* 0x00c */ int state;
    /* 0x010 */ float tState;           /* the state's start */
    /* 0x014 */ struct ALO *ploTarget;
    /* 0x018 */ void *pjtl;             /* the target's description (SafeHouse jtl: a pointer to its JTENT +0x4) */
    /* 0x01c */ float g1C;              /* a curve target's parameter (kind 3) */
    /* 0x020 */ float sTarget;          /* its distance / the description's parameter (SafeHouse s20) */
    /* 0x024 */ char unk_0x024[0x440 - 0x24];
    /* 0x440 */ REACH reach;            /* kinds 5 / 9 */
    /* 0x4fc */ int kAbility;           /* ACTOR +0x9BC: the ability started as kinds 11 / 12 (SafeHouse n9BC, 0x141D38) */
    /* 0x500 */ int f500;               /* kinds 11 / 12: hold the action */
    /* 0x504 */ int unk_0x504;
    /* 0x508 */ struct ASEG *paseg508;  /* kind 12's default clip */
    /* 0x50c */ struct ASEG *paseg50C;  /* kind 12's clip */
} INTERACT;

typedef struct ACTOR {
    /* 0x0000 */ SO so;
    /* PO fields (po.h PO; ACTOR derives SO -> PO -> STEP, cid 0x34 < 0x33 STEP < 0x32 PO) */
    /* 0x0150 */ struct POCTL *pctl;        /* the pad controller (SafeHouse PO ppadctl) */
    /* 0x0154 */ uint grfbtnForce;          /* buttons the object holds down by itself (SafeHouse grfbtnForced) */
    /* 0x0158 */ int unk_0x0158[4];
    /* 0x0168 */ struct PO *ppoUnk168;      /* a clone points it at itself (ClonePo) */
    /* 0x016c */ void *ptnCam;              /* camera tunnel (TN) used while in focus */
    /* 0x0170 */ int unk_0x0170[4];
    /* STEP fields (step.h STEP; SafeHouse step.h) */
    /* 0x0180 */ float uTurn;               /* gain of the turn toward the heading */
    /* 0x0184 */ int unk_0x0184[3];
    /* 0x0190 */ qword vecVel;              /* velocity the feet push toward, in the heading's frame (STEP: float[3]) */
    /* 0x01a0 */ float uGait;
    /* 0x01a4 */ int nMotion;               /* STEPMOTION_* */
    /* 0x01a8 */ float radHeading;          /* the heading (SetStepPhysHeading) */
    /* 0x01ac */ int unk_0x01ac;
    /* 0x01b0 */ struct MATRIX3 matHeading; /* rotation about z by radHeading */
    /* 0x01e0 */ qword posTarget;           /* STEPMOTION_Target's goal angular velocity */
    /* 0x01f0 */ float gScale;              /* SetStepPhysScale */
    /* 0x01f4 */ float vBrake[3];           /* STEPMOTION_Brake speeds; an SMP when the heading is smoothed (TurnActorNow) */
    /* 0x0200 */ float uBrake;
    /* 0x0204 */ int fNoContacts;
    /* 0x0208 */ struct XP *pxpFloor;       /* contact with the floor */
    /* 0x020c */ float tFloor;              /* when the floor contact was last there */
    /* 0x0210 */ float sFloorTarget;        /* the floor contact's target height */
    /* 0x0214 */ float sProbeDrop;          /* the second floor probe's depth below the first */
    /* 0x0218 */ qword *pposProbe0;         /* floor probe at the base: a point of the custom entry */
    /* 0x021c */ qword *pposProbe1;         /* the probe sProbeDrop below it */
    /* 0x0220 */ float sSupport;            /* radius of the floor-support triangles around pposProbe0 */
    /* 0x0224 */ int unk_0x0224[3];
    /* 0x0230 */ qword posFloor;            /* world point of vecBase */
    /* 0x0240 */ qword vecBase;             /* the object's base in its own frame */
    /* 0x0250 */ int unk_0x0250[2];
    /* 0x0258 */ SOPART *psoeCustom;        /* the custom entry (SafeHouse SOE) carrying the floor probes */
    /* 0x025c */ SOPART *psoeOther;         /* SOE: the second mesh (SetStepMesh) */
    /* 0x0260 */ float sSize;               /* SetStepPhysSize */
    /* 0x0264 */ int oidMesh;               /* tag of the entry the custom entry is made from */
    /* 0x0268 */ SOPART *psoeSource;        /* SOE: that entry (turned off) */
    /* 0x026c */ int unk_0x026c;            /* BHVSTK (STEP::bhvstk): the actor's own jobs (SafeHouse AISTACK stack) */
    /* 0x0270 */ int cJob;                  /* busy when positive (SafeHouse n270) */
    /* 0x0274 */ char unk_0x0274[0x2c0 - 0x274];   /* rest of the job stack; +0x294 CRV (SafeHouse crv294) */
    /* ACTOR's own fields */
    /* 0x02c0 */ JUMP jump;
    /* 0x04c0 */ INTERACT inter;
    /* 0x09d0 */ char unk_0x09d0[0x9e4 - 0x9d0];
    /* 0x09e4 */ int cSafeGround;           /* the safe ground (+0x9E0)'s entry count */
    /* 0x09e8 */ char unk_0x09e8[0xdfc - 0x9e8];
    /* 0x0dfc */ int cHealthMax;            /* the damage (+0xDF0) capacity */
    /* 0x0e00 */ int *pcHealth;             /* the damage counter */
    /* 0x0e04 */ char unk_0x0e04[0xf04 - 0xe04];
    /* 0x0f04 */ unsigned int stBinoc;      /* the binocucom (+0xF00)'s state, -1 by its init (SafeHouse nF04) */
    /* 0x0f08 */ char unk_0x0f08[0xf20 - 0xf08];
    /* 0x0f20 */ int nF20;                  /* the binocucom's view (-1 by its init) */
    /* 0x0f24 */ char unk_0x0f24[0xf38 - 0xf24];
    /* 0x0f38 */ struct PHOTOPROMPT *pprompt;
    /* 0x0f3c */ char unk_0x0f3c[0xf5c - 0xf3c];
    /* 0x0f5c */ struct LO *ploClimb;       /* the climb (+0xF50)'s object: the pipe climbed (SafeHouse ploF5C) */
    /* 0x0f60 */ float sClimb;              /* the distance along it (SafeHouse sCrvF50) */
    /* 0x0f64 */ char unk_0x0f64[0xfd0 - 0xf64];
    /* 0x0fd0 */ char watch[0x10];          /* the follower's watch (+0xFD0 sub-object) */
    /* 0x0fe0 */ char unk_0x0fe0[0x1000 - 0xfe0];
    /* 0x1000 */ int grfPlayer;             /* the actor's player bit (SafeHouse n1000) */
    /* 0x1004 */ char unk_0x1004[0x1024 - 0x1004];
    /* 0x1024 */ struct LO *ploZone;        /* the current player's camera zone (SafeHouse plo1024) */
    /* 0x1028 */ void *psmIdle;             /* the idle state machine (SafeHouse) */
    /* 0x102c */ void *psm102C;
    /* 0x1030 */ struct ASEGA *pasega;      /* the current animation (SafeHouse pasega) */
    /* 0x1034 */ void *psma;                /* the current state machine (SafeHouse psma) */
    /* 0x1038 */ char unk_0x1038[0x1040 - 0x1038];
    /* 0x1040 */ int nSide;                 /* the side the interaction faces, 1 flips it (SafeHouse n1040) */
    /* 0x1044 */ char unk_0x1044[0x1084 - 0x1044];
    /* 0x1084 */ void *prunScript;          /* the script runner driving it */
    /* 0x1088 */ char unk_0x1088[0x10dc - 0x1088];
    /* 0x10dc */ struct LO *ploFace;        /* the object faced (SafeHouse plo10DC) */
    /* 0x10e0 */ int grf10E0;
    /* 0x10e4 */ char unk_0x10e4[0x10e8 - 0x10e4];
    /* 0x10e8 */ struct LO *ploTarget;      /* the target picked (SafeHouse plo10E8) */
    /* 0x10ec */ int nTargetKind;           /* its kind: 4 a guard in reach (SafeHouse n10EC) */
    /* 0x10f0 */ char unk_0x10f0[0x10f8 - 0x10f0];
    /* 0x10f8 */ struct LO *ploLook;        /* the object looked at */
    /* 0x10fc */ int nLookKind;             /* its kind (the guard's rank, or an interest point's priority) */
    /* 0x1100 */ int fLookHeld;             /* the look target held, not chosen each frame (SafeHouse f1100) */
    /* 0x1104 */ char unk_0x1104[0x1148 - 0x1104];
    /* 0x1148 */ int fLook;
    /* 0x114c */ float tLookNext;
    /* 0x1150 */ char unk_0x1150[0x11a8 - 0x1150];
    /* 0x11a8 */ struct LO *pbooty;         /* the carried booty */
    /* 0x11ac */ char unk_0x11ac[0x11b4 - 0x11ac];
    /* 0x11b4 */ int stThrow;               /* jtthrow.state */
    /* 0x11b8 */ char unk_0x11b8[0x12fc - 0x11b8];
    /* 0x12fc */ int *pnPower;              /* "mpCur", the gadgets' power */
    /* 0x1300 */ int nPowerMax;             /* SafeHouse n1300 */
    /* 0x1304 */ char unk_0x1304[0x1318 - 0x1304];
    /* 0x1318 */ int n1318;
} ACTOR;

/* layout self-checks */
#define ACTOR_OFFSET_(t, m) ((unsigned int)&(((t *)0x10000)->m) - 0x10000)
typedef char ACTOR_check_so[sizeof(SO) == 0x150 ? 1 : -1];
typedef char ACTOR_check_jump[sizeof(JUMP) == 0x200 && ACTOR_OFFSET_(JUMP, state) == 0x1c ? 1 : -1];
typedef char ACTOR_check_reach[sizeof(REACH) == 0xbc && ACTOR_OFFSET_(INTERACT, sTarget) == 0x20 ? 1 : -1];
typedef char ACTOR_check_inter[sizeof(INTERACT) == 0x510 && ACTOR_OFFSET_(INTERACT, reach) == 0x440 &&
                               ACTOR_OFFSET_(INTERACT, paseg50C) == 0x50c ? 1 : -1];
typedef char ACTOR_check_a[ACTOR_OFFSET_(ACTOR, jump) == 0x2c0 && ACTOR_OFFSET_(ACTOR, inter) == 0x4c0 &&
                           ACTOR_OFFSET_(ACTOR, cSafeGround) == 0x9e4 ? 1 : -1];
typedef char ACTOR_check_b[ACTOR_OFFSET_(ACTOR, pcHealth) == 0xe00 && ACTOR_OFFSET_(ACTOR, pprompt) == 0xf38 &&
                           ACTOR_OFFSET_(ACTOR, grfPlayer) == 0x1000 && ACTOR_OFFSET_(ACTOR, ploZone) == 0x1024 ? 1 : -1];
typedef char ACTOR_check_c[ACTOR_OFFSET_(ACTOR, ploFace) == 0x10dc && ACTOR_OFFSET_(ACTOR, fLookHeld) == 0x1100 &&
                           ACTOR_OFFSET_(ACTOR, tLookNext) == 0x114c && ACTOR_OFFSET_(ACTOR, pbooty) == 0x11a8 ? 1 : -1];
typedef char ACTOR_check_step[ACTOR_OFFSET_(ACTOR, pctl) == 0x150 && ACTOR_OFFSET_(ACTOR, vecVel) == 0x190 &&
                              ACTOR_OFFSET_(ACTOR, matHeading) == 0x1b0 && ACTOR_OFFSET_(ACTOR, pxpFloor) == 0x208 &&
                              ACTOR_OFFSET_(ACTOR, vecBase) == 0x240 && ACTOR_OFFSET_(ACTOR, psoeSource) == 0x268 &&
                              ACTOR_OFFSET_(ACTOR, cJob) == 0x270 ? 1 : -1];
typedef char ACTOR_check_e[ACTOR_OFFSET_(ACTOR, ploClimb) == 0xf5c && ACTOR_OFFSET_(ACTOR, pasega) == 0x1030 &&
                           ACTOR_OFFSET_(ACTOR, nSide) == 0x1040 && ACTOR_OFFSET_(ACTOR, nTargetKind) == 0x10ec ? 1 : -1];
typedef char ACTOR_check_d[ACTOR_OFFSET_(ACTOR, stThrow) == 0x11b4 && ACTOR_OFFSET_(ACTOR, nPowerMax) == 0x1300 &&
                           ACTOR_OFFSET_(ACTOR, n1318) == 0x1318 ? 1 : -1];
#undef ACTOR_OFFSET_

#endif
