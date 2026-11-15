/* Sly 2 ACTOR layout (partial), for C and C++ sources.
 *
 * ACTOR (class id 0x34) derives from SO. Field offsets and names come from SafeHouse (FridiNaTor1's PC port,
 * Sly2-Release/actor.h and interact.h, "+0x..." offset comments; credited in CREDITS.md) and the matched code that
 * reads them. Only fields whose offsets the matched sources use are named; the spans between are unk_0xXXX padding.
 * The sub-objects (JUMP at +0x2C0, INTERACT at +0x4C0) keep SafeHouse's names where they are known.
 */
#ifndef ACTOR_H
#define ACTOR_H
#include "so.h"

struct ALO;
struct ACTOR;
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

/* the interaction (ACTOR +0x4C0; SafeHouse interact.h INTERACT): what a player does with an object it holds on to
 * or uses */
typedef struct INTERACT {
    /* 0x000 */ struct ACTOR *pactor;
    /* 0x004 */ float tBegin;           /* the action's start */
    /* 0x008 */ int kind;               /* the running interaction's kind (-1 none) */
    /* 0x00c */ int state;
    /* 0x010 */ float tState;           /* the state's start */
    /* 0x014 */ struct ALO *ploTarget;
    /* 0x018 */ char unk_0x018[0x440 - 0x18];
    /* 0x440 */ char reach[0x4fc - 0x440];   /* REACH (kinds 5 / 9) */
    /* 0x4fc */ int n4FC;               /* ACTOR +0x9BC (SafeHouse n9BC) */
    /* 0x500 */ int f500;               /* kinds 11 / 12: hold the action */
    /* 0x504 */ int unk_0x504;
    /* 0x508 */ struct ASEG *paseg508;  /* kind 12's default clip */
    /* 0x50c */ struct ASEG *paseg50C;  /* kind 12's clip */
} INTERACT;

typedef struct ACTOR {
    /* 0x0000 */ SO so;
    /* 0x0150 */ char unk_0x0150[0x270 - 0x150];
    /* 0x0270 */ int cJob;                  /* busy when positive (SafeHouse n270) */
    /* 0x0274 */ char unk_0x0274[0x2c0 - 0x274];
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
    /* 0x0f3c */ char unk_0x0f3c[0xfd0 - 0xf3c];
    /* 0x0fd0 */ char watch[0x10];          /* the follower's watch (+0xFD0 sub-object) */
    /* 0x0fe0 */ char unk_0x0fe0[0x1000 - 0xfe0];
    /* 0x1000 */ int grfPlayer;             /* the actor's player bit (SafeHouse n1000) */
    /* 0x1004 */ char unk_0x1004[0x1024 - 0x1004];
    /* 0x1024 */ struct LO *ploZone;        /* the current player's camera zone (SafeHouse plo1024) */
    /* 0x1028 */ char unk_0x1028[0x1084 - 0x1028];
    /* 0x1084 */ void *prunScript;          /* the script runner driving it */
    /* 0x1088 */ char unk_0x1088[0x10dc - 0x1088];
    /* 0x10dc */ struct LO *ploFace;        /* the object faced (SafeHouse plo10DC) */
    /* 0x10e0 */ int grf10E0;
    /* 0x10e4 */ char unk_0x10e4[0x10f8 - 0x10e4];
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
typedef char ACTOR_check_inter[sizeof(INTERACT) == 0x510 && ACTOR_OFFSET_(INTERACT, reach) == 0x440 &&
                               ACTOR_OFFSET_(INTERACT, paseg50C) == 0x50c ? 1 : -1];
typedef char ACTOR_check_a[ACTOR_OFFSET_(ACTOR, jump) == 0x2c0 && ACTOR_OFFSET_(ACTOR, inter) == 0x4c0 &&
                           ACTOR_OFFSET_(ACTOR, cSafeGround) == 0x9e4 ? 1 : -1];
typedef char ACTOR_check_b[ACTOR_OFFSET_(ACTOR, pcHealth) == 0xe00 && ACTOR_OFFSET_(ACTOR, pprompt) == 0xf38 &&
                           ACTOR_OFFSET_(ACTOR, grfPlayer) == 0x1000 && ACTOR_OFFSET_(ACTOR, ploZone) == 0x1024 ? 1 : -1];
typedef char ACTOR_check_c[ACTOR_OFFSET_(ACTOR, ploFace) == 0x10dc && ACTOR_OFFSET_(ACTOR, fLookHeld) == 0x1100 &&
                           ACTOR_OFFSET_(ACTOR, tLookNext) == 0x114c && ACTOR_OFFSET_(ACTOR, pbooty) == 0x11a8 ? 1 : -1];
typedef char ACTOR_check_d[ACTOR_OFFSET_(ACTOR, stThrow) == 0x11b4 && ACTOR_OFFSET_(ACTOR, nPowerMax) == 0x1300 &&
                           ACTOR_OFFSET_(ACTOR, n1318) == 0x1318 ? 1 : -1];
#undef ACTOR_OFFSET_

#endif
