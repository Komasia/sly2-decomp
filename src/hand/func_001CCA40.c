struct O { char pad[0xE0]; int grf; };
struct S { char pad[0x1000]; int grf; };
extern char g_sw[];
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *p, int a, int b, int c, int d, struct O **apo);
struct O *func_001CCA40(struct S *p, int n)
{
    struct O *apo[4];
    int c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x401, 0x14, n, 4, apo);
    int i;
    for (i = 0; i < c; i++) {
        if (apo[i]->grf & p->grf) return apo[i];
    }
    return 0;
}
