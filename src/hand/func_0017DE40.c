/* class: JOBBD (SafeHouse aijobs.cpp (0x17DE40): JOBBD done, st == -1). */
struct JOBBD {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;
};

int func_0017DE40(struct JOBBD *pjob)
{
    return pjob->st == -1;
}
