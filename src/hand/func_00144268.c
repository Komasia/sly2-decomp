/* HealActor: the base heal (0x1C4228), then the actor's health (through the damage part's pointer +0xE00) and power raised. */
void func_001C4228(void *pactor, int dHealth, int dPower);
void func_00144188(void *pactor, int a);
int NActorPower__FP5ACTOR(void *pactor);
void SetActorPower__FP5ACTORi(void *pactor, int a);
// name: SafeHouse port (HealActor)
void HealActor__FP5ACTORii(char *pactor, int dHealth, int dPower)
{
    func_001C4228(pactor, dHealth, dPower);
    func_00144188(pactor, **(int **)(pactor + 0xE00) + dHealth);   /* the damage part's health */
    SetActorPower__FP5ACTORi(pactor, NActorPower__FP5ACTOR(pactor) + dPower);
}
