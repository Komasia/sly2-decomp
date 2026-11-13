/* FActorTakesCharm: whether a hit takes a charm from the actor: only when func_001C41B8 allows it and the actor's
 * damage component (+0xDF0) is not in status 2. */
struct ACTOR;
struct DAMAGE;
int func_001C41B8(struct ACTOR *pactor);
int NDamageStatus(struct DAMAGE *pdamage) asm("NDamageStatus__FP5ACTOR");

// name: SafeHouse port (FActorTakesCharm)
int FActorTakesCharm__FP5ACTOR(struct ACTOR *pactor)
{
    if (!func_001C41B8(pactor))
        return 0;
    return NDamageStatus((struct DAMAGE *)((char *)pactor + 0xDF0)) != 2;
}
