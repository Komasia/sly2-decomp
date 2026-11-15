/* class: ACTOR's watch (the +0xFD0 sub-object; SafeHouse actor.h ACTOR::WATCH, "+0xFD0 (0x144638)"): its init,
 * binding the watch to its actor. The watch tracks the follower's progress toward its target point and recovers
 * the actor when it stops getting closer (UpdateActorWatch). */
struct ACTOR;
struct ACTORWATCH {
    /* 0x0 */ struct ACTOR *pactor;   /* the actor the watch belongs to */
};

void func_00144638(struct ACTORWATCH *pwatch, struct ACTOR *pactor)
{
    pwatch->pactor = pactor;
}
