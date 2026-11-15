/* FGuardHitMatters (0x207530): whether a hit counts against the guard: not when its damage (-dhp) is below the
 * guard's authored health, and not for zap kinds 0, 1, 0x80000 or 0x100000. */
struct CTMSG { char pad[0xC]; int zpk; int dhp; };
struct GUARD { char pad[0x338]; int nHealthMax; };
// name: SafeHouse port (FGuardHitMatters)
int FGuardHitMatters__FP5GUARDP5CTMSG(struct GUARD *pguard, struct CTMSG *pctm) { if (-pctm->dhp < pguard->nHealthMax) return 0; switch (pctm->zpk) { case 0: case 1: case 0x80000: case 0x100000: return 0; } return 1; }
