/* class: AIJOB (SafeHouse aijobs.cpp / aihit.cpp (0x177D20): its guard is busy - either of its two object lists
 * +0xF94 / +0xFA8 not empty). */
struct GUARD {
    /* 0x000 */ char pad0[0xf94];
    /* 0xf94 */ int fF94;   /* field: SafeHouse port */
    /* 0xf98 */ char padf98[0xfa8 - 0xf98];
    /* 0xfa8 */ int fFA8;   /* field: SafeHouse port */
};
struct AIJOB {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;   /* field: SafeHouse port */
};

int func_00177D20(struct AIJOB *pjob)
{
    struct GUARD *pguard = pjob->pguard;
    int fBusy = 0;
    if (pguard->fFA8 != 0 || pguard->fF94 != 0) {
        fBusy = 1;
    }
    return fBusy;
}
