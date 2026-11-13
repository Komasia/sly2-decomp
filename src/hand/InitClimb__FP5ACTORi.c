/* InitClimb: the climb (ACTOR +0xF50) initialized: its actor, state -1, the hand's place on the pipe in the climber's
 * frame {45, 0, 40} and the second point {45, 0, -20}. Layout: SafeHouse port (actor.h CLIMB). */
struct VECTOR3 { float x, y, z; };
struct CLIMB {
    /* 0x00 */ struct ACTOR *pactor;
    /* 0x04 */ int state;                /* SafeHouse: ACTOR::nSubF54 */
    /* 0x08 */ char pad8[0x30 - 0x8];
    /* 0x30 */ struct VECTOR3 posHand;   /* field: SafeHouse port */
    /* 0x3c */ char pad3C[0x40 - 0x3c];
    /* 0x40 */ struct VECTOR3 pos40;     /* field: SafeHouse port */
};

// name: SafeHouse port (InitClimb)
void InitClimb__FP5ACTORi(struct CLIMB *pclimb, struct ACTOR *pactor)
{
    struct VECTOR3 *pposHand = &pclimb->posHand;
    struct VECTOR3 *ppos40;
    pclimb->pactor = pactor;
    pclimb->state = -1;
    ppos40 = &pclimb->pos40;
    pclimb->posHand.x = 45.0f;
    pposHand->z = 40.0f;
    pposHand->y = 0;
    pclimb->pos40.x = 45.0f;
    ppos40->z = -20.0f;
    ppos40->y = 0;
}
