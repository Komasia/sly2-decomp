/* class: AIJOB (SafeHouse aihit.cpp, 0x177D70: its guard is a class-0x3C one with +0x108C set). */
struct GUARD {
    /* 0x0000 */ char pad0[0x108c];
    /* 0x108c */ int n108C;   /* field: SafeHouse port */
};
struct AIJOB {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;   /* field: SafeHouse port */
};
int FIsBasicDerivedFrom__FP5BASIC3CID(struct GUARD *pbasic, int cid);

int func_00177D70(struct AIJOB *pjob)
{
    int f = 0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->pguard, 0x3C) != 0) {
        f = pjob->pguard->n108C != 0;
    }
    return f;
}
