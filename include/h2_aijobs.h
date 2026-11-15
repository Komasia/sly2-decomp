/* Guard AI jobs of the 0x170000 module: JOBSCRIPT (runs a command list), JOBINVESTIGATE (0xAB, investigates a
 * noise), the hits (JOBHIT 0xA0..0xA3), JOBWAIT, JOBSLEEP, JOBB0 / JOBB1 (held / launched), JOBUSE, JOBSHOOT, JOBB2,
 * JOBSURROUND, JOBSTATION, JOBRAIL, JOBLADDER, the go-to (GOAL, NAVLINK, JOBGOTO, JOBLINK, JOBNAVPOINT), JOBBD and
 * JOBPATHSTEP. Layout: the matched code, names after SafeHouse (aijobs.h, aihit.h, aipursuit.h,
 * ainoise.h; field: SafeHouse port). */
#ifndef H2_AIJOBS_H
#define H2_AIJOBS_H
#include "aijob.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

struct CMD;
struct CMDLIST;
struct SAVEDSCRIPT;

typedef struct JOBSCRIPT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char unk_0x24[0x30 - 0x24];
    /* 0x30 */ struct CMDLIST *pcmdlist;
    /* 0x34 */ void *ploNear;           /* the object the commands are relative to */
    /* 0x38 */ struct CMD *pcmd;        /* the current command */
    /* 0x3c */ float tCmd;              /* when it started */
    /* 0x40 */ int fRunning;
    /* 0x44 */ struct SAVEDSCRIPT *psaved;
    /* 0x48 */ float radFace;
    /* 0x4c */ int fFromReact;
} JOBSCRIPT;

/* JOBINVESTIGATE states */
#define INVS_None       -1
#define INVS_Alerted     0
#define INVS_Going       1   /* going to the noise */
#define INVS_Looking     2   /* facing it, waiting */
#define INVS_Searching   3   /* searching around */
#define INVS_GivingUp    4
#define INVS_Paused      5   /* the game is paused */

typedef struct JOBINVESTIGATE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char unk_0x24[0x30 - 0x24];
    /* 0x30 */ int st;
    /* 0x34 */ float tSt;
    /* 0x38 */ float tEnd;              /* when it gives up */
    /* 0x3c */ float tSearch;           /* when it starts searching around */
    /* 0x40 */ float t40;
    /* 0x44 */ struct NOISE *pnoise;
    /* 0x48 */ int fNew;                /* a new noise to follow */
    /* 0x4c */ int unk_0x4c;
    /* 0x50 */ qword aposWay[4][2];     /* the search's places: the goal, then the place it is near */
    /* 0xd0 */ int iway;
} JOBINVESTIGATE;

/* A quadword vector as the VU code reads it: whole, or by component. */
#ifndef H2_QVEC
#define H2_QVEC
typedef union QVEC {
    qword q;
    float f[4];
} QVEC;
#endif

struct LO;

/* JOBHIT (0xA0, 0xC0 bytes): a hit - a move (JOBMOVE) playing the hit's kind entry, facing where the hit came from; the
 * base of JOBHIT1 (0xA1, nAnim 5), JOBHIT2 (0xA2, 6) and JOBHIT3 (0xA3, knocked out, 7). The hit's description is the
 * contact message's (CTMSG) fields copied from the reaction. Layout: SafeHouse port (aihit.h JOBHIT, ai.h AIMSG::HIT). */
typedef struct JOBHIT {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ struct LO *psource;      /* field: SafeHouse port - who hit the guard */
    /* 0x54 */ void *pvOther;           /* field: SafeHouse port */
    /* 0x58 */ struct LO *preceiver;    /* field: SafeHouse port */
    /* 0x5c */ unsigned int grfKind;    /* field: SafeHouse port (kind) - the hit's kind, one contact-filter bit */
    /* 0x60 */ int nAmount;             /* field: SafeHouse port (n) - the hit points it costs (negative) */
    /* 0x64 */ char pad64[0x70 - 0x64];
    /* 0x70 */ QVEC pos;                /* field: SafeHouse port - where it landed */
    /* 0x80 */ QVEC vec;                /* field: SafeHouse port - its push */
    /* 0x90 */ char pad90[0x94 - 0x90];
    /* 0x94 */ unsigned int grfAccepted; /* field: SafeHouse port (grf) */
    /* 0x98 */ char pad98[0xB0 - 0x98];
    /* 0xb0 */ float tJolt;             /* field: SafeHouse port (tB0) - when the camera jolts */
    /* 0xb4 */ float tEntryHit;         /* field: SafeHouse port (tB4) - when the guard's body entries strike back */
    /* 0xb8 */ char padB8[0xC0 - 0xB8];
} JOBHIT;

/* the hit kinds the hit jobs test (contact-filter bits) */
#define HITK_Sleep    0x80000    /* Bentley's sleep dart */
#define HITK_Launch   0x200000   /* a launching hit */

/* JOBWAIT states */
#define WAITS_None     -1
#define WAITS_Patrol    0   /* running the patrol's command list (JOBSCRIPT) */
#define WAITS_Pause     1   /* a pause in the patrol (standing) */
#define WAITS_Idle      2   /* nothing to do (standing) */
#define WAITS_Held      3   /* the guard is held still (FGuardStill) */

/* JOBWAIT (0xAA, 0x50 bytes): waiting between patrols. Layout: SafeHouse port (aijobs.h JOBWAIT). */
typedef struct JOBWAIT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ float tPause;            /* field: SafeHouse port (tA) - when the patrol pauses */
    /* 0x34 */ float tResume;           /* field: SafeHouse port (tB) - when the pause ends */
    /* 0x38 */ int st;                  /* field: SafeHouse port - WAITS_* */
    /* 0x3c */ float tSt;               /* field: SafeHouse port */
    /* 0x40 */ struct CMDLIST *pcmdlist; /* field: SafeHouse port - the patrol */
    /* 0x44 */ char pad44[0x50 - 0x44];
} JOBWAIT;

/* JOBSLEEP states */
#define SLEEPS_None    -1
#define SLEEPS_Asleep   0
#define SLEEPS_Waking   1

/* JOBSLEEP (0xAF, 0x60 bytes): asleep (Bentley's dart): a move (nAnim 0x10). Layout: SafeHouse port (aijobs.h). */
typedef struct JOBSLEEP {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ int stSleep;             /* field: SafeHouse port - SLEEPS_* */
    /* 0x54 */ float gSt;               /* field: SafeHouse port - the state, as a float */
    /* 0x58 */ float tWake;             /* field: SafeHouse port */
    /* 0x5c */ char pad5C[0x60 - 0x5C];
} JOBSLEEP;

/* JOBB0 states (held: reaction 6) */
#define HELDS_None     -1
#define HELDS_Grabbed   0
#define HELDS_Carried   1
#define HELDS_LetGo     2
#define HELDS_Thrown    3
#define HELDS_Extracted 4   /* Bentley's Health Extractor's hold */

/* JOBB0 (0xB0, 0x40 bytes): held (picked up by Murray, Bentley's Health Extractor). Layout: SafeHouse port (aijobs.h). */
typedef struct JOBB0 {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int stHeld;              /* field: SafeHouse port - HELDS_* */
    /* 0x34 */ float tHeld;             /* field: SafeHouse port */
    /* 0x38 */ float tNoise;            /* field: SafeHouse port - the last carried noise */
    /* 0x3c */ struct LO *ploHolder;    /* field: SafeHouse port */
} JOBB0;

/* JOBB1 states (a launched guard) */
#define LAUNCHS_None     -1
#define LAUNCHS_Rise      0   /* flying to the launch target */
#define LAUNCHS_Fall      1   /* falling (past the top) */
#define LAUNCHS_Lost      2   /* the target gone / its time over */
#define LAUNCHS_Land      3   /* landed */
#define LAUNCHS_Strike    4   /* the contextual strike: toward the striker */
#define LAUNCHS_Struck    5
#define LAUNCHS_Done      6

struct CTRLTARGET;

/* JOBB1 (0xB1, 0x70 bytes): a launched guard, then the contextual strike's target: a move (nAnim 0x17).
 * Layout: SafeHouse port (aijobs.h JOBB1). */
typedef struct JOBB1 {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ int stLaunch;            /* field: SafeHouse port - LAUNCHS_* */
    /* 0x54 */ float tLaunch;           /* field: SafeHouse port */
    /* 0x58 */ int nLaunch;             /* field: SafeHouse port - the launches so far */
    /* 0x5c */ struct LO *ploOwner;     /* field: SafeHouse port - the attacking actor */
    /* 0x60 */ int fTrack;              /* field: SafeHouse port - follow the owner's launch target */
    /* 0x64 */ struct CTRLTARGET *pctrlTarget; /* field: SafeHouse port - the launch's timed translation */
    /* 0x68 */ char pad68[0x70 - 0x68];
} JOBB1;

/* JOBUSE (0xAC, 0xA0 bytes): the use of an object (a chair, a ladder, a rope, a bar, else the ground): a move
 * (nAnim 15) at its place and orientation. Layout: SafeHouse port (aijobs.h JOBUSE). */
typedef struct JOBUSE {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ QVEC pos;                /* field: SafeHouse port - where */
    /* 0x60 */ struct LO *ploTarget;    /* field: SafeHouse port - the object (null after the ground's case) */
    /* 0x64 */ int fReverse;            /* field: SafeHouse port */
    /* 0x68 */ int nExtra;              /* field: SafeHouse port */
    /* 0x6c */ int fBasis;              /* field: SafeHouse port - mat is set */
    /* 0x70 */ qword mat[3];            /* field: SafeHouse port - its orientation */
} JOBUSE;

/* JOBSHOOT (0xAD, 0x40 bytes): the shot. Layout: SafeHouse port (aipursuit.h JOBSHOOT). */
typedef struct JOBSHOOT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - 0 shooting, -1 done */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ struct LO *ptarget;      /* field: SafeHouse port */
} JOBSHOOT;

/* JOBSHOOT states */
#define SHOOTS_None    -1
#define SHOOTS_Shoot    0

/* JOBB2 states */
#define B2S_None       -1
#define B2S_Stand       0   /* standing (JOBSTAND) */
#define B2S_Pursue      1   /* pursuing the selected object (JOBPURSUE) */
#define B2S_Held        2   /* standing while the guard is held still */

/* JOBB2 (0xB2, 0x50 bytes): the guard busy with objects (option 426's lists): every 1..2 s it selects the nearest
 * second-list object near the way to the best first-list object, else that one. Layout: SafeHouse port (aipursuit.h). */
typedef struct JOBB2 {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - B2S_* */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ struct LO *ploPreferred; /* field: SafeHouse port - the best first-list object */
    /* 0x3c */ struct LO *ploNear;      /* field: SafeHouse port - a second-list object on the way */
    /* 0x40 */ struct LO *ploSelected;  /* field: SafeHouse port */
    /* 0x44 */ float tChoose;           /* field: SafeHouse port - the next choice */
    /* 0x48 */ char pad48[0x50 - 0x48];
} JOBB2;

/* JOBSURROUND states */
#define SURS_None      -1
#define SURS_Stand      0   /* facing the target (JOBSTAND) */
#define SURS_Follow     1   /* following the path to its place around the target (JOBFOLLOW) */

/* JOBSURROUND (0xB3, 0x40 bytes): around the target. Layout: SafeHouse port (aipursuit.h). */
typedef struct JOBSURROUND {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - SURS_* */
    /* 0x34 */ char pad34[0x40 - 0x34];
} JOBSURROUND;

/* JOBSTATION states */
#define STATS_None     -1
#define STATS_Going     0   /* going to the point (JOBGOTO) */
#define STATS_Hurrying  1   /* hurrying after the object (JOBGOTO, move 0x1C) while it is far */
#define STATS_Held      2   /* facing it while the guard is held still */

/* JOBSTATION (0xB7, 0x70 bytes): the guard's station: a point in an object's frame. Layout: SafeHouse port. */
typedef struct JOBSTATION {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct LO *plo;          /* field: SafeHouse port - the station object */
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ qword pos;               /* field: SafeHouse port - the point in its frame */
    /* 0x50 */ int st;                  /* field: SafeHouse port - STATS_* */
    /* 0x54 */ float tSt;               /* field: SafeHouse port */
    /* 0x58 */ char pad58[0x60 - 0x58];
    /* 0x60 */ qword posLast;           /* field: SafeHouse port - the object's position at the last goal */
} JOBSTATION;

/* JOBRAIL (0xB8, 0x40 bytes): following the rail the guard is on (GUARD +0xF84). Layout: SafeHouse port (aijobs.h). */
typedef struct JOBRAIL {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ float uSpeed;            /* field: SafeHouse port */
    /* 0x3c */ float sGoal;             /* field: SafeHouse port */
} JOBRAIL;

/* JOBLADDER (0xB9, 0x40 bytes): climbing the ladder / pipe the guard is on (GUARD +0xF84, kind 1): its place moved
 * toward the goal end at the move's speed (eased). Layout: SafeHouse port (aijobs.h JOBLADDER). */
typedef struct JOBLADDER {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - 0 climbing, 1 at the goal */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ float sGoal;             /* field: SafeHouse port */
    /* 0x3c */ float gSpeed;            /* field: SafeHouse port - the eased climbing speed */
} JOBLADDER;

struct CRV;
struct NAVREGION;

/* GOAL (0x20): where a go-to heads - a path (its nearest point), an object (its position) or a fixed point; PosGoal
 * (0x1C1EC0) resolves it. Layout: SafeHouse port (aijobs.h GOAL). */
typedef struct GOAL {
    /* 0x00 */ struct CRV *pcrv;        /* field: SafeHouse port */
    /* 0x04 */ struct LO *plo;          /* field: SafeHouse port */
    /* 0x08 */ int pad8[2];
    /* 0x10 */ qword pos;               /* field: SafeHouse port */
} GOAL;

/* NAVLINK: a link between two navigation regions, walked or jumped through its records (goals).
 * Layout: SafeHouse port (navlink.h NAVLINK). */
typedef struct NAVLINK {
    /* 0x000 */ char pad0[0x50];
    /* 0x050 */ int crec;                   /* field: SafeHouse port - the records */
    /* 0x054 */ char pad54[0x60 - 0x54];
    /* 0x060 */ GOAL agoal[6];              /* field: SafeHouse port - the records' goals */
    /* 0x120 */ int kind;                   /* field: SafeHouse port - NAVLINKK_* */
    /* 0x124 */ struct NAVREGION *pregionBegin; /* field: SafeHouse port */
    /* 0x128 */ struct NAVREGION *pregionEnd;   /* field: SafeHouse port */
} NAVLINK;
#define NAVLINKK_Walked 0
#define NAVLINKK_Jumped 1

/* JOBGOTO states */
#define GOTOS_None      -1
#define GOTOS_Search     0   /* choosing the way */
#define GOTOS_Path       1   /* following a path to the goal (JOBFOLLOW) */
#define GOTOS_PathOpen   2   /* following a path to the goal's region (JOBFOLLOW) */
#define GOTOS_Link       3   /* crossing a navigation link (JOBLINK) */
#define GOTOS_Arrived    4   /* there, facing the object (JOBSTAND) */
#define GOTOS_Point      5   /* walking straight to the fallback point (JOBNAVPOINT) */

/* JOBGOTO (0xBA, 0xD0 bytes): a go-to: the goal reached by a path, a navigation link or straight to a point, the way
 * searched again every few seconds or when the navigation changes. Layout: SafeHouse port (aijobs.h JOBGOTO). */
typedef struct JOBGOTO {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - GOTOS_* */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ int nAnim;               /* field: SafeHouse port - the guard state of the walk (-1 none) */
    /* 0x3c */ int pad3C;
    /* 0x40 */ GOAL goal;               /* field: SafeHouse port */
    /* 0x60 */ GOAL goalCur;            /* field: SafeHouse port - the goal, or the link's end in its region */
    /* 0x80 */ GOAL goalFallback;       /* field: SafeHouse port - the point walked to when no path is found */
    /* 0xa0 */ float tSearch;           /* field: SafeHouse port - when the way was last searched */
    /* 0xa4 */ int nSerial;             /* field: SafeHouse port - the navigation's serial at that time */
    /* 0xa8 */ struct LO *plo;          /* field: SafeHouse port - the object gone to (followed, faced at the end) */
    /* 0xac */ int fAC;                 /* field: SafeHouse port */
    /* 0xb0 */ float gB0;               /* field: SafeHouse port */
    /* 0xb4 */ int cplink;              /* field: SafeHouse port - the found path's links (CNavLinkPath, 1 at most) */
    /* 0xb8 */ NAVLINK *aplink[1];      /* field: SafeHouse port */
    /* 0xbc */ int fDirect;             /* field: SafeHouse port - straight to the goal, no navigation */
    /* 0xc0 */ int fInexact;            /* field: SafeHouse port (fC0) - a link path that only gets near will do */
} JOBGOTO;

/* JOBBD states */
#define BDS_None     -1
#define BDS_Alerted   0   /* the alerted move, facing the object */
#define BDS_Away      1   /* running to the point farthest from it */
#define BDS_Held      2   /* standing while held still */

/* JOBBD (0xBD, 0x50 bytes): kept away from an object (the reaction 0x12, e.g. Guttural Roar).
 * Layout: SafeHouse port (aijobs.h JOBBD). */
typedef struct JOBBD {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port - BDS_* */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ struct LO *ploFrom;      /* field: SafeHouse port - the object kept away from */
    /* 0x3c */ float tChoose;           /* field: SafeHouse port - the point's last choice */
    /* 0x40 */ float tLeft;             /* field: SafeHouse port - the time left (FLT_MAX for the roar) */
} JOBBD;

/* JOBLINK states */
#define LINKS_None   -1
#define LINKS_Record  0   /* walking / jumping to the current record */
#define LINKS_Point   1   /* walking straight to it (JOBNAVPOINT) */

/* JOBLINK (0xBE): crossing a navigation link record by record. Layout: SafeHouse port (aijobs.h JOBLINK). */
typedef struct JOBLINK {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ NAVLINK *plink;          /* field: SafeHouse port */
    /* 0x34 */ int irec;                /* field: SafeHouse port - the record walked to */
    /* 0x38 */ int st;                  /* field: SafeHouse port - LINKS_* */
    /* 0x3c */ float tSt;               /* field: SafeHouse port */
    /* 0x40 */ float tEnd;              /* field: SafeHouse port - the walk's deadline */
} JOBLINK;

/* JOBNAVPOINT (0xBF, 0x50 bytes): to a way-point, dropped on the floor (else snapped up to a surface), walked to or
 * put there. Layout: SafeHouse port (aijobs.h JOBNAVPOINT). */
typedef struct JOBNAVPOINT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ GOAL goal;               /* field: SafeHouse port */
} JOBNAVPOINT;

/* JOBPATHSTEP (0xC0, 0x60 bytes): steps along a path - its JOBGOTO child sent a step further each time it arrives.
 * Layout: SafeHouse port (aijobs.h JOBPATHSTEP). */
typedef struct JOBPATHSTEP {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct CRV *pcrv;        /* field: SafeHouse port */
    /* 0x34 */ int fForward;            /* field: SafeHouse port */
    /* 0x38 */ float s;                 /* field: SafeHouse port - the distance on the path (-1: not yet) */
    /* 0x3c */ int pad3C;
    /* 0x40 */ qword pos;               /* field: SafeHouse port - the current step's point */
    /* 0x50 */ struct LO *plo50;        /* field: SafeHouse port - the goto's object */
    /* 0x54 */ int n54;                 /* field: SafeHouse port - the goto's fAC */
    /* 0x58 */ int fFromReact;          /* field: SafeHouse port - straight (the goto's fDirect), no path spans */
} JOBPATHSTEP;

#endif
