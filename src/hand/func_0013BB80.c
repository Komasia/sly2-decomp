/* ResetProjectileInstance: a pooled projectile made ready again: the base reset (0x1CB518), no impact, no end time,
 * its own launcher, its motion free, its contacts on, not stuck, out of its parent. Layout: SafeHouse port (projectile.cpp). */
struct BOMB { char pad[0x154]; float tEnd; char pad2[0x174 - 0x158]; int fHit; char pad3[0x1e8 - 0x178]; int paloAttach; };
extern float D_002A4B20;   /* FLT_MAX: no end time */
void func_001CB518(struct BOMB *);
void SetProjectileLauncher__FP3ALOP2LO(struct BOMB *, struct BOMB *);
void SetAloCnstrLin__FP3ALOi(struct BOMB *, int);
void SetAloCnstrAng__FP3ALOi(struct BOMB *, int);
void SetAloContactsOff__FP3ALOi(struct BOMB *, int);
void ReparentBooty__FP3ALOii(struct BOMB *, int, int);
// name: SafeHouse port (ResetProjectileInstance)
void ResetProjectileInstance__FP2LO(struct BOMB *pbomb) {
    func_001CB518(pbomb);
    pbomb->fHit = 0;
    pbomb->tEnd = D_002A4B20;
    SetProjectileLauncher__FP3ALOP2LO(pbomb, pbomb);
    SetAloCnstrLin__FP3ALOi(pbomb, 0);
    SetAloCnstrAng__FP3ALOi(pbomb, 0);
    SetAloContactsOff__FP3ALOi(pbomb, 0);
    pbomb->paloAttach = 0;
    ReparentBooty__FP3ALOii(pbomb, 0, 0xf);
}
