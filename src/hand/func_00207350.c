typedef int qword __attribute__((mode(TI)));
/* the concurrently playing response action (+0xF00) */
struct ACTIONOBJ { char pad[0xC0]; void *pkinde; };
struct GUARD {
    char pad0[0x28]; unsigned long grfLo;
    char pad1[0x208 - 0x30]; int pxpFloor; char pad1b[0x218 - 0x20C]; qword *pposProbe0;
    char pad2[0x26C - 0x21C]; char bhvstk[0x34C - 0x26C]; int pasega34C;
    char pad3[0x48C - 0x350]; int f48C; char pad4[0x498 - 0x490]; void *pwatchA; void *pwatchB;
    char pad5[0x4A4 - 0x4A0]; int f4A4; char pad6[0x4B0 - 0x4A8]; qword pos4B0;
    char pad7[0xF00 - 0x4C0]; struct ACTIONOBJ *pactionF00; char pad8[0xF0C - 0xF04]; int pctrlF0C;
    char pad9[0xFBC - 0xF10]; int nMode; char padA[0xFD0 - 0xFC0]; char move[0x10];
};
extern qword D_002A2DD0;
void UpdateStep__FP4STEPf(struct GUARD *pguard);
void UpdateGuardTimedMode__FP5GUARD(struct GUARD *pguard);
void RefreshGuardTargets__FP5GUARD(struct GUARD *pguard);
int FKindeDone__FP5KINDE(void *pkinde);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, struct ACTIONOBJ *paction, int n, qword pos);
void UpdateGuardActionAim__FP5GUARD(struct GUARD *pguard);
void NextPocketPrize__FP2LO(struct GUARD *pguard);
void UpdateWatchA__FP6WATCHA(void *pv);
void UpdateWatchB__FP6WATCHB(void *pv);
void UpdateJobs__FP5ACTOR(void *pv);
void func_002097E0(void *pv);
int FAsegaRetracted(int pasega) asm("FAsegaRetracted__FP5ASEGA");
void func_001306A8(int *ppasega);   /* RetractAsegaPp */

/* UpdateStepguard (0x207350): GUARD vt slot 16: the STEP update; then, in the world and not in mode 14 (frozen):
 * the timed modes, the targets, the response action ended when its animation is done, the action aim, the pocket's
 * next prize, the two ground watchers, the job stack, the current move, the +0x34C animation dropped once retracted,
 * and +0x4B0 following the floor probe while f4A4 is set and there is a floor. Field names: SafeHouse port. */
void UpdateStepguard__FP9STEPGUARDf(struct GUARD *pguard)
{
    UpdateStep__FP4STEPf(pguard);
    if (!((pguard->grfLo >> 60) & 1))
        return;
    if (pguard->nMode == 0xE)   /* frozen */
        return;
    UpdateGuardTimedMode__FP5GUARD(pguard);
    RefreshGuardTargets__FP5GUARD(pguard);
    if (pguard->pactionF00 && FKindeDone__FP5KINDE(pguard->pactionF00->pkinde))
        SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pguard, 0, 0, D_002A2DD0);
    if (pguard->pctrlF0C)
        UpdateGuardActionAim__FP5GUARD(pguard);
    if (pguard->f48C)
        NextPocketPrize__FP2LO(pguard);
    UpdateWatchA__FP6WATCHA(pguard->pwatchA);
    UpdateWatchB__FP6WATCHB(pguard->pwatchB);
    UpdateJobs__FP5ACTOR(pguard->bhvstk);
    func_002097E0(pguard->move);
    if (pguard->pasega34C && FAsegaRetracted(pguard->pasega34C))
        func_001306A8(&pguard->pasega34C);
    if (pguard->f4A4 && pguard->pxpFloor)
        pguard->pos4B0 = *pguard->pposProbe0;
}
