/* UpdateActorWatch: the follower's progress / recovery check, once a second while the actor is busy (a job or a
 * script). In hands-off mode the step guards in contact with the actor fade out (unless their script job holds them).
 * Otherwise, while the actor walks (a script's go-to, or its follow job 0xA8 in state 0 / 1) and has got less than
 * 30 units closer to the watched point since the last check, it is recovered to the ground at that point.
 * Layout: SafeHouse port (actor.h ACTOR::WATCH, actorai.cpp UpdateActorWatch). */
typedef int qword __attribute__((mode(TI)));
struct SCPTCMD { int k; };                                  /* a script command: its kind */
struct RUNSCRIPT { char pad[0x40]; struct SCPTCMD *pcmdCur; };  /* the script runner: its current command */
struct CTEND { int pad[2]; void *plo; void *pxC; char pad2[0x30]; };   /* one end of a contact: its object */
struct CONTACT { struct CTEND actend[2]; char pad[0xAC - 0x80]; struct CONTACT *pcontactNext; };
struct CTLINK { struct CONTACT *pcontact; struct CTLINK *pctlinkNext; };
struct CONTACTS { char pad[0x64]; struct CTLINK *pctlinkFirst; };   /* the actor's contacts (+0xEC; layout unsure) */
struct ACTOR {
    /* 0x0000 */ char pad0[0xEC];
    /* 0x00ec */ struct CONTACTS *pcontacts;
    /* 0x00f0 */ char pad2[0x2DC - 0xF0];
    /* 0x02dc */ int stJump;                  /* jump.state: -1 when not jumping */
    /* 0x02e0 */ char pad3[0x1084 - 0x2E0];
    /* 0x1084 */ struct RUNSCRIPT *prunScript;   /* field: SafeHouse port - the script runner driving it */
};
struct GUARD { char pad[0x130]; float g130; };   /* a step guard in contact (+0x130: meaning unknown; the task event is sent only when it is >= 0) */
struct AIJOB { char pad[0x4C]; int st; };        /* a job's state (JOBFOLLOW +0x4C) */
/* the actor's watch (ACTOR +0xFD0; SafeHouse actor.h ACTOR::WATCH) */
struct ACTORWATCH {
    /* 0x00 */ struct ACTOR *pactor;
    /* 0x04 */ char pad[0xC];
    /* 0x10 */ qword pos;      /* field: SafeHouse port - the follower's target point */
    /* 0x20 */ float s;        /* field: SafeHouse port - the distance last checked */
    /* 0x24 */ float t;        /* field: SafeHouse port - the next check */
    /* 0x28 */ int fActive;    /* field: SafeHouse port - recovery suspends job input/update */
};
#define SCPTCMD_GoTo 0x24       /* the script's go-to command (SafeHouse FScptActorGoingTo) */
#include "cid.h"
#include "clock.h"
extern float D_002BD2D0;   /* 1: the time between checks */
extern float D_002BD2D4;   /* 30: the least progress per second */
extern char g_sw[];
extern char g_game[];
int func_00144068(struct ACTOR *pactor);   /* the actor is busy (a job or a script) */
int IsSwHandsOff__FP2SW(void *);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct GUARD *pguard, int cid);
struct AIJOB *func_00205458(void *pactor, int cid);   /* the actor's job of a class */
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int nEvent, struct GUARD *pguard);
void FadeAloOut__FP3ALOf(struct GUARD *pguard, float dt);
qword PosOfLo__FP2LO(void *p);
int FDropOnGround__FP6VECTORffiPv(float, float, qword *, int, int);
int FSnapPosToSurfaceAbove__FP6VECTOR(qword *);
void RecoverTo__FP5ACTORG9VU_VECTOR(struct ACTOR *pactor, qword pos);

static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

/* which end of the contact is the actor */
static inline int IOther(struct ACTOR *pactor, struct CONTACT *pcontact)
{
    return pactor == pcontact->actend[0].plo ? 0 : 1;
}

// name: SafeHouse port (UpdateActorWatch)
void UpdateActorWatch__FP5ACTOR(struct ACTORWATCH *pwatch)
{
    if (pwatch->fActive) {
        if (pwatch->pactor->stJump == -1)
            pwatch->fActive = 0;
        return;
    }
    if (!func_00144068(pwatch->pactor))
        return;
    if (g_clock.t < pwatch->t)
        return;
    pwatch->t = g_clock.t + D_002BD2D0;
    if (IsSwHandsOff__FP2SW(g_sw)) {
        int fAny = 0;
        struct CTLINK *pctlink;
        for (pctlink = pwatch->pactor->pcontacts->pctlinkFirst; pctlink; pctlink = pctlink->pctlinkNext) {
            struct CONTACT *pcontact;
            for (pcontact = pctlink->pcontact; pcontact; pcontact = pcontact->pcontactNext) {
                int i = IOther(pwatch->pactor, pcontact);
                struct GUARD *pguard = pcontact->actend[1 - i].plo;
                if (FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_STEPGUARD)) {
                    struct AIJOB *pjob = func_00205458(pguard, CID_JOBSCRIPT);
                    if (!pjob || !pjob->st) {
                        if (0.0f <= pguard->g130)
                            BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x17 /* task event */, pguard);
                        FadeAloOut__FP3ALOf(pguard, 0.5f);
                        fAny = 1;
                    }
                }
            }
        }
        if (fAny)
            return;
    }
    if (pwatch->pactor->prunScript) {
        if (pwatch->pactor->prunScript->pcmdCur->k != SCPTCMD_GoTo)
            return;
    } else {
        struct AIJOB *pjob = func_00205458(pwatch->pactor, CID_JOBACTORFOLLOW);
        if (!pjob)
            return;
        {
            int st = pjob->st;
            if (st >= 2)
                return;
            if (st < 0)
                return;
        }
    }
    {
        qword pos = PosOfLo__FP2LO(pwatch->pactor);
        float s = GDist(pos, pwatch->pos);
        if (pwatch->s - s < D_002BD2D4 * D_002BD2D0) {
            qword posRecover = pwatch->pos;
            if (FDropOnGround__FP6VECTORffiPv(100.0f, -150.0f, &posRecover, 0, 0) || FSnapPosToSurfaceAbove__FP6VECTOR(&posRecover)) {
                RecoverTo__FP5ACTORG9VU_VECTOR(pwatch->pactor, posRecover);
                pwatch->fActive = 1;
            }
        }
        pwatch->s = s;
    }
}
