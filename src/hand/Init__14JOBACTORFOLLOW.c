/* JOBACTORFOLLOW::Init (AIJOB vt slot 7): a follow job run by a gang actor: the follow's init (0x177E80) and the
 * actor's speed 1. Layout: SafeHouse port (actorai.h JOBACTORFOLLOW). */
struct JOBACTORFOLLOW {
    /* 0x00 */ char pad0[0xd0];
    /* 0xd0 */ float uSpeedActor;   /* field: SafeHouse port */
};
void func_00177E80(struct JOBACTORFOLLOW *pjob);   /* JOBFOLLOW's init */

// name: SafeHouse port (JOBACTORFOLLOW::Init)
void Init__14JOBACTORFOLLOW(struct JOBACTORFOLLOW *pjob)
{
    func_00177E80(pjob);
    pjob->uSpeedActor = 1.0f;
}
