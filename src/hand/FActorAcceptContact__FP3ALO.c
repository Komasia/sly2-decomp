/* FActorAcceptContact: an actor's contact test is its damage component's (ACTOR +0xDF0). */
struct ALO;
struct DAMAGE;
struct CTMSG;
void FAcceptDamage(struct DAMAGE *pdamage) asm("FAcceptDamage__FP5ACTORP5CTMSG");

// name: SafeHouse port (FActorAcceptContact)
void FActorAcceptContact__FP3ALO(struct ALO *palo)
{
    FAcceptDamage((struct DAMAGE *)((char *)palo + 0xDF0));
}
