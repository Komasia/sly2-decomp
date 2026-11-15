/* FActorImmune: an actor is immune to msg while its binoculars' +0x20 is 1, in jump state 0x15, while the object
 * D_003D4A54 is the current player (0x1C40C0), else as its damage part says. */
extern void *D_003D4A54;
int func_001C40C0(void *pactor);
int FDamageImmune__FP5ACTORi(void *pactor, int msg);
// name: SafeHouse port (FActorImmune)
int FActorImmune__FP5ACTORi(char *pactor, int msg)
{
    if (*(int *)(pactor + 0xF20) == 1 /* binoculars +0x20 */) return 1;
    if (*(int *)(pactor + 0x2DC) == 0x15 /* jump state */) return 1;
    if (D_003D4A54 && func_001C40C0(D_003D4A54)) return 1;
    return FDamageImmune__FP5ACTORi(pactor + 0xDF0, msg);
}
