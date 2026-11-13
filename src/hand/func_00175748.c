/* class: JOBACT (SafeHouse aichase.cpp / aipursuit.cpp (0x175748): JOBACT done, st == -1). */
struct JOBACT {
    /* 0x00 */ char pad0[0x34];
    /* 0x34 */ int st;
};

int func_00175748(struct JOBACT *pjob)
{
    return pjob->st == -1;
}
