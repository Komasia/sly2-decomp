/* SpendActorPower: the ability's power cost (the table D_002BCD00 +0xC) taken from the actor's power; the time noted. */
struct ABILITYDEF { int a, b, c, mpCost; int pad[4]; };   /* the abilities' table (0x20 bytes each) */
extern struct ABILITYDEF D_002BCD00[];
extern float g_clock;
int NActorPower__FP5ACTOR(void *pactor);
void SetActorPower__FP5ACTORi(void *pactor, int a);
// name: SafeHouse port (gadget.h SpendActorPower, orig 0x141CD0)
void SpendActorPower__FP5ACTORi(char *pactor, int idAbility)
{
    if (idAbility != -1) SetActorPower__FP5ACTORi(pactor, NActorPower__FP5ACTOR(pactor) - D_002BCD00[idAbility].mpCost);
    *(float *)(pactor + 0x1304) = g_clock;   /* when power was last spent */
}
