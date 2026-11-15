/* func_00209790 (0x209790): MOVEREF: the current move cleared - its job and the
 * heading lock, the guard's STEP::vecVel zeroed, the guard woken (SafeHouse aijobs.cpp). */
struct AIJOB;
struct GUARD {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ int vecVel[3];   /* STEP::vecVel */
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
    int *anVel;
    pmove->pjob = 0;
    pguard = pmove->pguard;
    pmove->fHeadingLocked = 0;
    anVel = pguard->vecVel;
    anVel[2] = 0;
    anVel[1] = 0;
    pguard->vecVel[0] = 0;
    WakeAlo__FP3ALO(pmove->pguard);
}
