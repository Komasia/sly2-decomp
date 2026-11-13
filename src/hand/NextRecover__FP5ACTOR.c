/* NextRecover (a damage state's next step): the actor of the damage sub-object (ACTOR +0x9E0) recovers
 * (RecoverActorTo with none). Source: SafeHouse port (damage.cpp). */
struct ACTOR;
struct DAMAGE {
    /* 0x0 */ struct ACTOR *pactor;
};
void RecoverActorTo__FP5ACTORPv(struct ACTOR *pactor, void *pv);

// name: SafeHouse port (NextRecover, damage.cpp)
void NextRecover__FP5ACTOR(struct DAMAGE *pdmg)
{
    RecoverActorTo__FP5ACTORPv(pdmg->pactor, 0);
}
