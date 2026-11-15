/* InitGait (0x20B840): a gait (SafeHouse actanim.h GAIT) for its actor and footstep sound: volumes 0.6 at mix 0 and
 * 1 at mix 1. */
struct GAIT { void *palo; char pad[0x8C]; int sfx; float gVolLo; float gVolHi; };
// name: SafeHouse port (InitGait)
void InitGait__FP4GAITii(struct GAIT *pgait, void *palo, int sfx) {
  pgait->palo = palo;
  pgait->sfx = sfx;
  pgait->gVolHi = 1.0f;
  pgait->gVolLo = 0.6f;
}
