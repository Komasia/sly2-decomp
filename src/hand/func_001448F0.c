/* SetActorWatchTarget: the actor's watch takes a new target point (unless a recovery is under way or the point is
 * within 10 of the old one): the distance to it now, and the next check a second from now. Layout: SafeHouse port
 * (actor.h ACTOR::WATCH, actorai.cpp SetActorWatchTarget). */
typedef int qword __attribute__((mode(TI)));
/* the actor's watch (ACTOR +0xFD0); the distance is stored through an int view here (the original code converts
 * the float distance with a qmfc2 straight into an integer register) */
struct ACTORWATCH {
    /* 0x00 */ void *pactor;
    /* 0x04 */ char pad[0xC];
    /* 0x10 */ qword pos;      /* field: SafeHouse port - the follower's target point */
    /* 0x20 */ int s;          /* field: SafeHouse port - the distance last checked (a float's bits) */
    /* 0x24 */ float t;        /* field: SafeHouse port - the next check */
    /* 0x28 */ int fActive;    /* field: SafeHouse port - recovery suspends job input/update */
};
#include "clock.h"
extern float D_002BD2D8;   /* 10: a smaller move keeps the target */
extern float D_002BD2D0;   /* 1: the time between checks */
qword PosOfLo__FP2LO(void *p);
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
/* the distance, its float bits in an int */
static __inline__ int IDist(qword a, qword b)
{
    qword d, t;
    int g;
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
// name: SafeHouse port (SetActorWatchTarget)
void SetActorWatchTarget__FP5ACTORG9VU_VECTOR(struct ACTORWATCH *pwatch, qword pos)
{
    if (pwatch->fActive == 0) {
        qword posActor;
        int fNear = GDist(pwatch->pos, pos) < D_002BD2D8;
        if (fNear) return;
        pwatch->pos = pos;
        posActor = PosOfLo__FP2LO(pwatch->pactor);
        pwatch->s = IDist(posActor, pwatch->pos);
        pwatch->t = g_clock.t + D_002BD2D0;
    }
}
