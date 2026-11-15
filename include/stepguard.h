/* Sly 2 GUARD layout (partial), for C and C++ sources.
 *
 * GUARD is class 0x38 STEPGUARD (include/cid.h; classes.tsv: base STEP, 0x1010 bytes; the guard classes 0x39..0x43
 * derive from it). The matched code's function names call the type GUARD (FGuardState__FP5GUARDi, ...), with
 * STEPGUARD in a few vtable method names (HandleStepguardMessage__FP9STEPGUARD5MSGIDPv), so both names are given.
 * Field offsets and names come from SafeHouse (FridiNaTor1's PC port, Sly2-Release/guard.h, "+0x..." offset
 * comments; credited in CREDITS.md) and the matched code that reads them. Only fields the matched sources use are
 * named; the spans between are unk_0xXXX padding. The guard's own fields start after STEP at +0x2C0. Fields of the
 * derived guard classes (past +0x1010) are not here.
 */
#ifndef STEPGUARD_H
#define STEPGUARD_H
#include "step.h"

struct TARGETREC;
struct DETECTOR;
struct WATCHB;
struct CTRLPOS;
struct ASEG;
struct ASEGA;

typedef struct GUARD {
    /* 0x000 */ STEP step;
    /* 0x2c0 */ ulong grfState;            /* the state mask (GRFGS bits; FGuardState / SetGuardStateMask) */
    /* 0x2c8 */ int unk_0x2c8;
    /* 0x2cc */ float tWaitA0, tWaitA1;     /* the waits' range (FLT_MAX by InitLo) */
    /* 0x2d4 */ float tWaitB0, tWaitB1;
    /* 0x2dc */ int savedPatrol[3];        /* SAVEDSCRIPT: the place in the patrol command list */
    /* 0x2e8 */ void *pcmdlistPatrol;      /* the patrol command list (EOPID 273) */
    /* 0x2ec */ void *pcmdlistHome;        /* a go-to its home */
    /* 0x2f0 */ void *pcmdHome;
    /* 0x2f4 */ int unk_0x2f4[3];
    /* 0x300 */ qword posHome;
    /* 0x310 */ float radHome;
    /* 0x314 */ int unk_0x314[6];
    /* 0x32c */ int f32C;                  /* busy (0x207598) */
    /* 0x330 */ int fKnockoutNotified;     /* the one-time knockout notification */
    /* 0x334 */ int n334;
    /* 0x338 */ int nHealthMax;            /* EOPID 254: the authored health, in tenths */
    /* 0x33c */ int nHealth;               /* EOPID 255: the hit points left, in tenths */
    /* 0x340 */ int n340;
    /* 0x344 */ int n344;
    /* 0x348 */ struct ASEG *pasegBlock;   /* the block's clip */
    /* 0x34c */ struct ASEGA *pasega34C;
    /* 0x350 */ uint agrfHit[3];           /* the hits that matter by state */
    /* 0x35c */ int unk_0x35c;
    /* 0x360 */ float g360;
    /* 0x364 */ int fNear;
    /* 0x368 */ float lmNearCarry[2];
    /* 0x370 */ float lmNear[2];
    /* 0x378 */ float sNear;
    /* 0x37c */ int fFar;
    /* 0x380 */ float lmFar[2];
    /* 0x388 */ float sFar;
    /* 0x38c */ struct LO *ploPursued;     /* the pursued object (its splice) */
    /* 0x390 */ struct LO *ploTarget;
    /* 0x394 */ int ccidTarget;            /* the classes it looks for (up to 3) */
    /* 0x398 */ int acidTarget[3];
    /* 0x3a4 */ int cdetentryGenerated;
    /* 0x3a8 */ int ccidExcluded;          /* excluded target classes (up to 5) */
    /* 0x3ac */ int acidExcluded[5];
    /* 0x3c0 */ int ccidImmediate;         /* immediate target classes (up to 2) */
    /* 0x3c4 */ int acidImmediate[2];
    /* 0x3cc */ struct TARGETREC *ptarget3CC;  /* the pursued object's record (aipursuit) */
    /* 0x3d0 */ int n3D0;
    /* 0x3d4 */ int n3D4;
    /* 0x3d8 */ int unk_0x3d8[7];
    /* 0x3f4 */ struct LO *plo3F4;         /* option 304 */
    /* 0x3f8 */ struct LO *plo3F8;         /* option 305 */
    /* 0x3fc */ char unk_0x3fc[0x48c - 0x3fc];
    /* 0x48c */ int f48C;
    /* 0x490 */ int unk_0x490;
    /* 0x494 */ struct LO *plo494;         /* option 306 */
    /* 0x498 */ void *pwatchA;             /* ground watcher A */
    /* 0x49c */ struct WATCHB *pwatchB;    /* ground watcher B */
    /* 0x4a0 */ int f4A0;
    /* 0x4a4 */ int f4A4;
    /* 0x4a8 */ int unk_0x4a8[2];
    /* 0x4b0 */ qword pos4B0;
    /* 0x4c0 */ int ckinde;                /* the animation kinds (h6_guard.h KINDE): count */
    /* 0x4c4 */ int unk_0x4c4[3];
    /* 0x4d0 */ char akinde[0x400];        /* KINDE[32] */
    /* 0x8d0 */ char aakinde[0xdb0 - 0x8d0];   /* three arrays of 26 per-state kinds */
    /* 0xdb0 */ char k2play[0xe20 - 0xdb0];    /* K2PLAY: the kind-2 entries' player */
    /* 0xe20 */ char k3play[0xe60 - 0xe20];    /* K3PLAY: the directional entries' player */
    /* 0xe60 */ struct LO *ploAlarm;       /* the alarm's template */
    /* 0xe64 */ int nE64;
    /* 0xe68 */ int nE68;
    /* 0xe6c */ float dtGiveUpMin;         /* the search's give-up time range */
    /* 0xe70 */ float dtGiveUpMax;
    /* 0xe74 */ struct LO *ploLeash;       /* option 327 */
    /* 0xe78 */ int nSearchKind;
    /* 0xe7c */ int unk_0xe7c[4];
    /* 0xe8c */ struct ASEG *pasegE8C;
    /* 0xe90 */ struct ASEGA *pasegaE90;
    /* 0xe94 */ uint cRegion;              /* its navigation regions (up to 8) */
    /* 0xe98 */ int aRegion[8];
    /* 0xeb8 */ char unk_0xeb8[0xf00 - 0xeb8];
    /* 0xf00 */ struct LO *ploResponse;    /* the concurrently playing response action */
    /* 0xf04 */ float tNextAction;         /* the next action's time (the selector's cooldown) */
    /* 0xf08 */ void *pactionAim;          /* the aimed action */
    /* 0xf0c */ void *pctrlAim;            /* its aim controller */
    /* 0xf10 */ XF *pxfAimTarget;          /* the target's frame */
    /* 0xf14 */ int unk_0xf14[3];
    /* 0xf20 */ qword posAimTarget;        /* the target point in that frame */
    /* 0xf30 */ float gF30, gF34;          /* options 320 / 321 */
    /* 0xf38 */ int unk_0xf38;
    /* 0xf3c */ int fStriking;
    /* 0xf40 */ int unk_0xf40;
    /* 0xf44 */ float tNextAlarm;
    /* 0xf48 */ float gF48, gF4C;          /* option 298 */
    /* 0xf50 */ int unk_0xf50[4];
    /* 0xf60 */ int fShooting;             /* set by its clip's events 0x31 / 0x32 */
    /* 0xf64 */ struct DETECTOR *pdet;     /* its detector (cid 0x10 oid 648) */
    /* 0xf68 */ struct LO *ploStation;
    /* 0xf6c */ int unk_0xf6c;
    /* 0xf70 */ qword posStation;
    /* 0xf80 */ int kMove;                 /* how it moves (-1 walking, 0 a chair, 1 a ladder, 2 a bar, 3) */
    /* 0xf84 */ struct LO *ploMove;        /* what it moves on */
    /* 0xf88 */ float sMove;               /* its place along that object's curve */
    /* 0xf8c */ int nMoveKind;
    /* 0xf90 */ struct LO *ploHands;       /* its hands' point (EOPID 325) */
    /* 0xf94 */ int cploAttack;            /* option 426's first list: the objects it attacks */
    /* 0xf98 */ struct LO *aploAttack[4];
    /* 0xfa8 */ int cploTurnTo;            /* option 426's second list: the ones it turns to when near */
    /* 0xfac */ struct LO *aploTurnTo[4];
    /* 0xfbc */ int nMode;
    /* 0xfc0 */ float tMode;
    /* 0xfc4 */ struct CTRLPOS *pscale;    /* the kind-12 scale controller */
    /* 0xfc8 */ int fStill;
    /* 0xfcc */ struct LO *ploFace;        /* the stand job faces it */
    /* 0xfd0 */ char move[0x18];           /* MOVEREF */
    /* 0xfe8 */ uint grfMove;              /* 2 a walk, 4, 1, 8 (from the table) */
    /* 0xfec */ struct LO *ploFEC;         /* option 331 */
    /* 0xff0 */ float uGait, tGait;
    /* 0xff8 */ float tFF8;
    /* 0xffc */ int cActivationLocks;      /* job locks keep the guard active */
    /* 0x1000 */ int fSpawned;             /* placed by a spawner */
    /* 0x1004 */ int unk_0x1004[3];
} GUARD;   /* 0x1010 bytes */
typedef GUARD STEPGUARD;

/* layout self-checks */
#define GUARD_OFFSET_(m) ((unsigned int)&(((GUARD *)0x10000)->m) - 0x10000)
typedef char GUARD_check_a[sizeof(STEP) == 0x2c0 && GUARD_OFFSET_(grfState) == 0x2c0 && GUARD_OFFSET_(posHome) == 0x300 &&
                           GUARD_OFFSET_(nHealthMax) == 0x338 && GUARD_OFFSET_(ploPursued) == 0x38c ? 1 : -1];
typedef char GUARD_check_b[GUARD_OFFSET_(ccidImmediate) == 0x3c0 && GUARD_OFFSET_(n3D4) == 0x3d4 &&
                           GUARD_OFFSET_(plo3F4) == 0x3f4 && GUARD_OFFSET_(f48C) == 0x48c && GUARD_OFFSET_(pwatchB) == 0x49c &&
                           GUARD_OFFSET_(akinde) == 0x4d0 && GUARD_OFFSET_(ploAlarm) == 0xe60 ? 1 : -1];
typedef char GUARD_check_c[GUARD_OFFSET_(nSearchKind) == 0xe78 && GUARD_OFFSET_(pasegE8C) == 0xe8c &&
                           GUARD_OFFSET_(aRegion) == 0xe98 && GUARD_OFFSET_(ploResponse) == 0xf00 &&
                           GUARD_OFFSET_(posAimTarget) == 0xf20 && GUARD_OFFSET_(fStriking) == 0xf3c &&
                           GUARD_OFFSET_(fShooting) == 0xf60 && GUARD_OFFSET_(posStation) == 0xf70 ? 1 : -1];
typedef char GUARD_check_d[GUARD_OFFSET_(kMove) == 0xf80 && GUARD_OFFSET_(cploTurnTo) == 0xfa8 && GUARD_OFFSET_(nMode) == 0xfbc &&
                           GUARD_OFFSET_(move) == 0xfd0 && GUARD_OFFSET_(grfMove) == 0xfe8 &&
                           GUARD_OFFSET_(cActivationLocks) == 0xffc && sizeof(GUARD) == 0x1010 ? 1 : -1];
#undef GUARD_OFFSET_

#endif
