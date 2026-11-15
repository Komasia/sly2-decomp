typedef struct CRef { int m_tagk; int m_tag; } CRef;
/* SW: the progress keys of the play time, of the current episode and (per episode) of its percentage */
struct G { char pad[0x3B1C]; void *poptTimePlayed; char pad2[0x3B28 - 0x3B20]; void *poptEpisode; char pad3[0x3B7C - 0x3B2C]; void *apoptPercent[1]; };
struct TASKMGR { int a[4]; int oidJob; int oidTask; int oidQueued; };
extern struct G g_sw;
extern struct TASKMGR g_game;
extern void *D_002DEB4C;   /* the save to apply after the load */
extern char D_003DA530[];
extern char D_002A3828[];   /* the hub world */
CRef *NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_001D9880(void *p);
void ApplyVibrationSetting__Fv(void);
void func_001DD888(void *p);
void *func_00210B98(int n);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct G *psw, void *p, int a, int b, int c, int d);
/* StartGameFromSave: start the game of a save: a new game (no play time) shows the intro menu when it is up, else
 * transitions to the first world queuing task 0x62F; a saved game goes to its episode's world - the hub when the
 * episode is complete or has none. */
// name: SafeHouse port (StartGameFromSave)
void StartGameFromSave__FP2SW(void *pv)
{
    CRef ref;
    float tPlayed;
    register int n __asm__("$16"); /* register pin: n lives in s0 in the target */
    void *pchzWorld;
    void *poptPercent;
    NProgress(&ref, g_sw.poptTimePlayed, pv);
    tPlayed = *(float *)&ref.m_tag;
    Decref(&ref);
    if (func_001D9880(D_003DA530) && tPlayed == 0.0f) {
        ApplyVibrationSetting__Fv();
        func_001DD888(D_003DA530);
        return;
    }
    if (tPlayed == 0.0f) {
        D_002DEB4C = pv;
        g_game.oidJob = -1;
        g_game.oidTask = -1;
        g_game.oidQueued = 0x62F;
        RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, func_00210B98(0), 0x189, -1, 0x48, -1);
        return;
    }
    {
        struct G *psw = &g_sw;
        D_002DEB4C = pv;
        g_game.oidJob = -1;
        g_game.oidTask = -1;
        g_game.oidQueued = -1;
        NProgress(&ref, psw->poptEpisode, pv);
    }
    __asm__ __volatile__(""); /* ordering-only: ends the -1 constant's dependence chain at the call */
    n = ref.m_tag;
    Decref(&ref);
    pchzWorld = func_00210B98(n);
    poptPercent = g_sw.apoptPercent[n];
    n = 0;
    if (poptPercent) {
        NProgress(&ref, poptPercent, pv);
        n = ref.m_tag;
        Decref(&ref);
    }
    if (n >= 100 || !pchzWorld) {
        pchzWorld = D_002A3828;
        __asm__ __volatile__("" : : "r"(n)); /* allocation-only: keeps n live past the compare */
    }
    RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, pchzWorld, 0x189, -1, 0x40, -1);
}
