/* class: CID_45, the turrets (vt slot 41 = Clone; SafeHouse turret.cpp): ClonePo, then a mount +0x1D0 that was the
 * original becomes the copy. */
struct TURRET {
    /* 0x000 */ char pad0[0x1d0];
    /* 0x1d0 */ struct TURRET *pturretMount;
};
void ClonePo__FP2POT0(struct TURRET *ppo, struct TURRET *ppoBase);

struct TURRET *func_00225A68(struct TURRET *pturret, struct TURRET *pturretBase)
{
    struct TURRET *pmount;
    ClonePo__FP2POT0(pturret, pturretBase);
    pmount = pturret->pturretMount;
    if (pmount == pturretBase) {
        pturret->pturretMount = pturret;
    }
    return pmount;
}
