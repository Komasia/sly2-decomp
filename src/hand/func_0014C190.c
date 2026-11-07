extern char g_sw[];
void *func_00210B98(void *p);
void RequestTransition__FP2SWPUc3OIDT2iT2(void *a, void *b, int c, int d, int e, int f);
void func_0014C190(void *p)
{
    void *v = func_00210B98(p);
    if (!v) v = func_00210B98(0);
    RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, v, 0x189, -1, 0, -1);
}
