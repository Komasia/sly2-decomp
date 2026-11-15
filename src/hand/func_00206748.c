extern float D_002A8610;   /* -FLT_MAX */
extern int D_002C3CF0;
/* the guard's detector */
struct DETECTOR { char pad[0xF0]; int fAlways; int fNever; };
struct GUARD {
    char p0[0x2DC]; int saved2DC[3]; int pcmdlistPatrol; char p1[0x330 - 0x2EC]; int fKnockoutNotified; char p2[0x360 - 0x334]; float g360;
    char p3[0x390 - 0x364]; int ploTarget; char p4[0x484 - 0x394]; int cPocket, iPocket, fPocketReady, fPocketMore; char p5[0x4A0 - 0x494]; int f4A0;
    char p6[0xE94 - 0x4A4]; int cRegion; char p7[0xF64 - 0xE98]; struct DETECTOR *pdet; int ploF68; char p8[0xF94 - 0xF6C]; int cploF98;
    char p9[0xFA8 - 0xF98]; int cploFAC; char p10[0xFC8 - 0xFAC]; int fStill, ploFCC; char p11[0xFF4 - 0xFD0]; float tGaitFF4;
    char p12[0x1000 - 0xFF8]; int nSpawnMode;
};
void func_001CB5D0(struct GUARD *pguard);
void DetachGuardMove__FP5GUARD(struct GUARD *pguard);
void *s1_memset(void *pv, int c, int cb) asm("memset");
void SetGuardPursued__FP5GUARDP2LO(struct GUARD *pguard, int plo);
void func_002088E0(struct GUARD *pguard);   /* clears the target classes */
void SetPocketMode__FP2LOi(struct GUARD *pguard, int mode);
void SetGuardMode__FP5GUARDi(struct GUARD *pguard, int mode);
/* func_00206748 (0x206748): GUARD vt slot 27, the placement-end notification: the pooled guard's per-use state is
 * cleared before its instance is reused (the children's slot 27, its move detached, the patrol and saved script, the
 * allowed regions, the detector's always/never flags, the option object lists, the target and pursuit, the pocket,
 * the knockout notification, the station; the pocket and guard modes back to -1). Field names: SafeHouse port
 * (guardstart.cpp DetachGuardSlot27). */
void func_00206748(struct GUARD *pguard)
{
    int fOne;
    func_001CB5D0(pguard);
    DetachGuardMove__FP5GUARD(pguard);
    pguard->pcmdlistPatrol = 0;
    s1_memset(pguard->saved2DC, 0, 0xC);
    pguard->cRegion = 0;
    pguard->pdet->fAlways = 0;
    pguard->pdet->fNever = 0;
    pguard->cPocket = 0;
    pguard->iPocket = 0;
    pguard->fPocketReady = 0;
    pguard->fPocketMore = 0;
    pguard->cploF98 = 0;
    pguard->cploFAC = 0;
    pguard->ploTarget = 0;
    SetGuardPursued__FP5GUARDP2LO(pguard, 0);
    func_002088E0(pguard);
    fOne = 1;
    pguard->fKnockoutNotified = 0;
    pguard->ploF68 = 0;
    pguard->fStill = 0;
    pguard->ploFCC = 0;
    pguard->g360 = -10.0f;
    pguard->f4A0 = fOne;
    pguard->tGaitFF4 = D_002A8610;
    pguard->nSpawnMode = D_002C3CF0;
    SetPocketMode__FP2LOi(pguard, -1);
    SetGuardMode__FP5GUARDi(pguard, -1);
}
