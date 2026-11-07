extern void *D_003D4A54;
int func_001C40C0(void *p);
int FDamageImmune__FP5ACTORi(void *p, int a);
// name: SafeHouse port (FActorImmune)
int FActorImmune__FP5ACTORi(char *p, int a)
{
    if (*(int *)(p + 0xF20) == 1) return 1;
    if (*(int *)(p + 0x2DC) == 0x15) return 1;
    if (D_003D4A54 && func_001C40C0(D_003D4A54)) return 1;
    return FDamageImmune__FP5ACTORi(p + 0xDF0, a);
}
