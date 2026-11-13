/* class: JOBLINK (SafeHouse aijobs.cpp (0x17E570): the link crossed, its state -1). */
struct JOBLINK {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ int st;
};

int func_0017E570(struct JOBLINK *pjob)
{
    return pjob->st == -1;
}
