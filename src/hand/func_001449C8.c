/* class: ACTOR's watch (the +0xFD0 sub-object, SafeHouse actor.h ACTOR::WATCH; called by UpdateActor): whether a
 * recovery is under way (it suspends the actor's job input / update). */
struct ACTORWATCH {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int fActive;   /* field: SafeHouse port - recovery suspends job input/update */
};

int func_001449C8(struct ACTORWATCH *pwatch)
{
    return pwatch->fActive;
}
