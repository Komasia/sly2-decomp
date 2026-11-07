extern char g_cm[];
void func_001C3FF0(void *p, int b);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *g, int a, void *h, void *p, int z);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *g, int a, int b, void *h, void *p, int z);
void func_00225AE8(void *p, int b)
{
    func_001C3FF0(p, b);
    if (b) SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, 9, g_cm + 0x5F0, p, 0);
    else RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 0xF, 9, g_cm + 0x5F0, p, 0);
}
