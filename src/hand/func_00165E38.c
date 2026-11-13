typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct G { char pad[0x3B1C]; void *f3b1c; char pad2[0x3B28 - 0x3B20]; void *f3b28; char pad3[0x3B7C - 0x3B2C]; void *a3b7c[1]; };
struct Q { int a[4]; int f10; int f14; int f18; };
extern struct G g_sw;
extern struct Q g_game;
extern void *D_002DEB4C;
extern char D_003DA530[];
extern char D_002A3828[];
CRef *NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_001D9880(void *p);
void ApplyVibrationSetting__Fv(void);
void func_001DD888(void *p);
void *func_00210B98(int n);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct G *pg, void *p, int a, int b, int c, int d);
// name: SafeHouse port (StartGameFromSave)
void StartGameFromSave__FP2SW(void *pv)
{
    CRef ref;
    float g;
    register int n __asm__("$16"); /* register pin: n lives in s0 in the target */
    void *ps;
    void *prop;
    NProgress(&ref, g_sw.f3b1c, pv);
    g = *(float *)&ref.m_tag;
    Decref(&ref);
    if (func_001D9880(D_003DA530) && g == 0.0f) {
        ApplyVibrationSetting__Fv();
        func_001DD888(D_003DA530);
        return;
    }
    if (g == 0.0f) {
        D_002DEB4C = pv;
        g_game.f10 = -1;
        g_game.f14 = -1;
        g_game.f18 = 0x62F;
        RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, func_00210B98(0), 0x189, -1, 0x48, -1);
        return;
    }
    {
        struct G *pg = &g_sw;
        D_002DEB4C = pv;
        g_game.f10 = -1;
        g_game.f14 = -1;
        g_game.f18 = -1;
        NProgress(&ref, pg->f3b28, pv);
    }
    __asm__ __volatile__(""); /* ordering-only: ends the -1 constant's dependence chain at the call */
    n = ref.m_tag;
    Decref(&ref);
    ps = func_00210B98(n);
    prop = g_sw.a3b7c[n];
    n = 0;
    if (prop) {
        NProgress(&ref, prop, pv);
        n = ref.m_tag;
        Decref(&ref);
    }
    if (n >= 100 || !ps) {
        ps = D_002A3828;
        __asm__ __volatile__("" : : "r"(n)); /* allocation-only: keeps n live past the compare */
    }
    RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, ps, 0x189, -1, 0x40, -1);
}
