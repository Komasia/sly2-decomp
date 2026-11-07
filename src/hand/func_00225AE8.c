extern char g_cm[];
void SetCmFocusObject__FP2LOi(void *p, int b);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *g, int a, void *h, void *p, int z);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *g, int a, int b, void *h, void *p, int z);
// name: SafeHouse port (SetTurretFocus)
void SetTurretFocus__FP2LOi(void *p, int b)
{
    SetCmFocusObject__FP2LOi(p, b);
    if (b) SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, 9, g_cm + 0x5F0, p, 0);
    else RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 0xF, 9, g_cm + 0x5F0, p, 0);
}
