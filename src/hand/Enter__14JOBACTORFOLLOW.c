/* JOBACTORFOLLOW::Enter (AIJOB vt slot 8): the follow's enter, then the actor watches the steered point (+0x80;
 * SetActorWatchTarget on the actor's +0xFD0). Layout: SafeHouse port (aijobs.h JOBFOLLOW). */
typedef int VU_VECTOR __attribute__((mode(TI)));   /* a 128-bit vector register */
struct ACTOR {
    /* 0x000 */ char pad0[0xfd0];
    /* 0xfd0 */ char watch[0x10];   /* the watch */
};
struct JOBACTORFOLLOW {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct ACTOR *pactor;   /* field: SafeHouse port */
    /* 0x14 */ char pad14[0x80 - 0x14];
    /* 0x80 */ VU_VECTOR pos;          /* field: SafeHouse port - the steered point */
};
void Enter__9JOBFOLLOW(struct JOBACTORFOLLOW *pjob);
void SetActorWatchTarget__FP5ACTORG9VU_VECTOR(void *pwatch, VU_VECTOR pos);

// name: SafeHouse port (JOBACTORFOLLOW::Enter)
void Enter__14JOBACTORFOLLOW(struct JOBACTORFOLLOW *pjob)
{
    Enter__9JOBFOLLOW(pjob);
    SetActorWatchTarget__FP5ACTORG9VU_VECTOR(pjob->pactor->watch, pjob->pos);
}
