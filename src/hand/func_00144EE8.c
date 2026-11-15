/* JOBACTORWALK::FAtGoal: the walk is at its goal when its follow job (the child, +0x18) has arrived or is in state 2.
 * Layout: SafeHouse port (actorai.h JOBACTORWALK, aijobs.h JOBFOLLOW). */
struct JOBFOLLOW {
    /* 0x00 */ char pad0[0x4C];
    /* 0x4c */ int st;                 /* field: SafeHouse port */
};
struct JOBACTORWALK {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ struct JOBFOLLOW *pchild;   /* field: SafeHouse port (AIJOB) - the follow job */
};
int FArrived__9JOBFOLLOW(struct JOBFOLLOW *pjob);
// name: SafeHouse port (JOBACTORWALK::FAtGoal)
int FAtGoal__12JOBACTORWALK(struct JOBACTORWALK *pjob)
{
    struct JOBFOLLOW *pjobFollow = pjob->pchild;
    int fAtGoal = 0;
    if (FArrived__9JOBFOLLOW(pjobFollow) || pjobFollow->st == 2) fAtGoal = 1;
    return fAtGoal;
}
