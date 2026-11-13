/* FGuardLaunchAllowed: the generic launch / grab acceptance gate: a source derived from cid 0x36 always launches a
 * guard that is not of cid 0x3A / 0x3D nor the special guard D_002DD648; otherwise only a surprised guard.
 * Source: SafeHouse port (aihit.cpp). */
struct GUARD;
struct LO;
extern struct GUARD *D_002DD648;   /* SafeHouse: g_pguard3F */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int FGuardSurprised__FP5GUARDP2LOUl(struct GUARD *pguard, struct LO *plo, int grf);

// name: SafeHouse port (FGuardLaunchAllowed)
int FGuardLaunchAllowed__FP5GUARDP2LOi(struct GUARD *pguard, struct LO *ploSource, int grf)
{
    if (FIsBasicDerivedFrom__FP5BASIC3CID(ploSource, 0x36) && !FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x3A) &&
        !FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x3D) && pguard != D_002DD648)
        return 1;
    return FGuardSurprised__FP5GUARDP2LOUl(pguard, ploSource, grf);
}
