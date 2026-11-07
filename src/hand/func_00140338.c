struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern char g_sw[];
struct G { char pad[0x4A4]; int n4A4; };
extern struct G g_cm;
int func_00210AE0(void);
void ShowCoinCounter__FP2SW(void *p);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *p, int a, int b, int c, int d, int e);
void func_001618B0(void *p);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void func_00140338(void)
{
    if (func_00210AE0()) {
        ShowCoinCounter__FP2SW(g_sw);
        if (CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x605, 0x5F, 0, 0, 0)) func_001618B0(g_sw);
        SetSource__4CSndPv(PsndNewPlain__Fi(0x32), 0);
        *(float *)(g_sw + 0x4754) = g_clock.t;
        g_cm.n4A4++;
    }
}
