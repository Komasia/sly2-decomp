extern void *D_003D4A54;
int func_001C40C0(void *p);
int func_001A2230(void *p, int a);
int func_00140ED8(char *p, int a)
{
    if (*(int *)(p + 0xF20) == 1) return 1;
    if (*(int *)(p + 0x2DC) == 0x15) return 1;
    if (D_003D4A54 && func_001C40C0(D_003D4A54)) return 1;
    return func_001A2230(p + 0xDF0, a);
}
