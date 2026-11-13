/* NActorDamageStatus: an actor's damage status is its damage component's (ACTOR +0xDF0). */
struct LO;
struct DAMAGE;
void NDamageStatus(struct DAMAGE *pdamage) asm("NDamageStatus__FP5ACTOR");

// name: SafeHouse port (NActorDamageStatus)
void NActorDamageStatus__FP2LO(struct LO *plo)
{
    NDamageStatus((struct DAMAGE *)((char *)plo + 0xDF0));
}
