/* class: MOVEREF, a guard's current move (SafeHouse aijobs.cpp, orig 0x209790: the move cleared - its job and the
 * heading lock, the guard's +0x190 row zeroed, the guard woken). */
struct AIJOB;
struct GUARD {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ int an190[3];
};
struct MOVEREF {
    /* 0x0 */ struct AIJOB *pjob;      /* field: SafeHouse port */
    /* 0x4 */ int fHeadingLocked;      /* field: SafeHouse port */
    /* 0x8 */ int n8;
    /* 0xc */ struct GUARD *pguard;    /* field: SafeHouse port */
};
void WakeAlo__FP3ALO(struct GUARD *palo);

void func_00209790(struct MOVEREF *pmove)
{
    struct GUARD *pguard;
    int *an;
    pmove->pjob = 0;
    pguard = pmove->pguard;
    pmove->fHeadingLocked = 0;
    an = pguard->an190;
    an[2] = 0;
    an[1] = 0;
    pguard->an190[0] = 0;
    WakeAlo__FP3ALO(pmove->pguard);
}
