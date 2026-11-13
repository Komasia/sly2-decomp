/* class: JOBMOVE (SafeHouse ainoise.cpp / aichase.cpp (0x174FB8): the move done, st == 1). */
struct JOBMOVE {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;
};

int func_00174FB8(struct JOBMOVE *pjob)
{
    return pjob->st == 1;
}
