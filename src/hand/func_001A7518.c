extern int D_002E2050, D_002E2054;
extern void *D_002DD644;
extern int D_002BE538;
extern char g_sw[], D_003D9E70[], g_joy[], g_cm[], g_clock[];
void func_0023B7D8(void);
void func_001A7970(void);
void func_001613A8(void);
void PswUpdateTransition__FP2SW(void *);
void UpdateJoy(void *) asm("UpdateJoy__FP3JOY");
void UpdateCd(void) asm("UpdateCd__Fv");
void StartupCm(void *) asm("StartupCm__Fv");
void UpdateClock__FP5CLOCKi(void *, int);
void RegisterSwPass__FPv(void *);
void func_001D9648(void *);
void OpenFrame(void) asm("OpenFrame__Fv");
int FAnimatedOverlayDrawNormal__FPc(void *);
void RenderSw(void *) asm("RenderSw__FP2SW");
void func_00157FA0(void *);
void UpdateRecyclable(void *) asm("UpdateRecyclable__3CGc");
void DrawAnimatedOverlayFrame__FPv(void *);
void func_00160A98(void);
void func_001A7518(int a, int b)
{
    func_0023B7D8();
    D_002E2050 = a;
    D_002E2054 = b;
    func_001A7970();
    func_001613A8();
    for (;;) {
        PswUpdateTransition__FP2SW(g_sw);
        UpdateJoy(g_joy);
        UpdateCd();
        StartupCm(g_cm);
        UpdateClock__FP5CLOCKi(g_clock, 0);
        RegisterSwPass__FPv(g_sw);
        func_001D9648(D_003D9E70);
        OpenFrame();
        if (!D_002DD644 || FAnimatedOverlayDrawNormal__FPc(D_002DD644)) {
            RenderSw(g_sw);
            func_00157FA0(g_sw);
            UpdateRecyclable(D_003D9E70);
        }
        if (D_002DD644)
            DrawAnimatedOverlayFrame__FPv(D_002DD644);
        func_00160A98();
        D_002BE538++;
    }
}
