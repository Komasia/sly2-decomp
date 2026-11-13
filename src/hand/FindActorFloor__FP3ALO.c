/* FindActorFloor: an actor's floor is its step's (FindStepFloor); during a jump animation state (the jump at
 * +0x2C0, its state +0x1C != -1) the ledge contacts it cannot use are pruned. Layout: SafeHouse port (actor.h JUMP). */
struct ALO;
struct JUMP {
    /* 0x00 */ char pad0[0x1c];
    /* 0x1c */ int state;   /* field: SafeHouse port - the animation state (-1 none) */
};
struct ACTOR {
    /* 0x000 */ char pad0[0x2c0];
    /* 0x2c0 */ struct JUMP jump;
};
void FindStepFloor(struct ACTOR *pactor) asm("FindStepFloor__FP3ALO");
void PruneJumpLedgeXps(struct JUMP *pjump) asm("PruneJumpLedgeXps__FP5ACTOR");

// name: SafeHouse port (FindActorFloor)
void FindActorFloor__FP3ALO(struct ACTOR *pactor)
{
    FindStepFloor(pactor);
    if (pactor->jump.state != -1)
        PruneJumpLedgeXps(&pactor->jump);
}
