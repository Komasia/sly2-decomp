extern int D_002C3D10[];
extern char g_sw[];
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *p, int a, int b, int c, int d, int e);
void func_00208920(void *p, int n);
void func_00206DB0(void *p)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        int n = D_002C3D10[i];
        if (CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x605, n, 0, 0, 0))
            func_00208920(p, n);
    }
}
