/* class: JOBFOLLOW (SafeHouse aijobs.cpp (0x178D80): the follow in state 3). */
struct JOBFOLLOW {
    /* 0x00 */ char pad0[0x4c];
    /* 0x4c */ int st;
};

int func_00178D80(struct JOBFOLLOW *pjob)
{
    return pjob->st == 3;
}
