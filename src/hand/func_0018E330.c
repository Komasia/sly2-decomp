extern char g_sw[];
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *g, int a, int b, int c, int cMax, void **ap);
void UpdatePocketMode__FP2LO(void *p);
void func_0018E330(void)
{
    void *ap[32];
    int c, i;
    c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x505, 0x38, 0, 0x20, ap);
    for (i = 0; i < c; i++)
        UpdatePocketMode__FP2LO(ap[i]);
}
