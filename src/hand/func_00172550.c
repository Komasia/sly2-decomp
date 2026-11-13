/* class: AIJOB (SafeHouse aijobs.cpp (0x172550): the job's state -1). */
struct AIJOB {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;
};

int func_00172550(struct AIJOB *pjob)
{
    return pjob->st == -1;
}
