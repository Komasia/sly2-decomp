/* func_001A7518 (0x1A7518): the game's main (Sly 1 main.c main's shape): keeps argc / argv (D_002E2050 / D_002E2054), runs the
 * startup stages (func_001A7970) and 0x1613A8, then the frame loop: world transition, joypad, CD, camera, clock, the
 * world's update pass and the HUD; then the frame is drawn (render + draw the world, recycle) unless an animated
 * overlay (D_002DD644) draws instead; the overlay frame, the frame closed, the frame count (D_002BE538) bumped. */
extern int g_argc __asm__("D_002E2050"), g_argv __asm__("D_002E2054");
extern void *g_poverlay __asm__("D_002DD644");  /* the animated overlay playing, if any */
extern int g_cframe __asm__("D_002BE538");
extern char g_sw[], D_003D9E70[], g_joy[], g_cm[], g_clock[];
void __main__Fv(void);
void func_001A7970(void);
void func_001613A8(void);
void PswUpdateTransition__FP2SW(void *);
void UpdateJoy(void *) asm("UpdateJoy__FP3JOY");
void UpdateCd(void) asm("UpdateCd__Fv");
void StartupCm(void *) asm("StartupCm__Fv");
void UpdateClock__FP5CLOCKi(void *, int);
void RegisterSwPass__FPv(void *);
void UpdateHudWidgets__FP2DL(void *);
void OpenFrame(void) asm("OpenFrame__Fv");
int FAnimatedOverlayDrawNormal__FPc(void *);
void RenderSw(void *) asm("RenderSw__FP2SW");
void DrawSw(void *) asm("DrawSw__FP2SW");
void UpdateRecyclable(void *) asm("UpdateRecyclable__3CGc");
void DrawAnimatedOverlayFrame__FPv(void *);
void CloseFrame__Fv(void);
void func_001A7518(int argc, int argv)
{
    __main__Fv();
    g_argc = argc;
    g_argv = argv;
    func_001A7970();
    func_001613A8();
    for (;;) {
        PswUpdateTransition__FP2SW(g_sw);
        UpdateJoy(g_joy);
        UpdateCd();
        StartupCm(g_cm);
        UpdateClock__FP5CLOCKi(g_clock, 0);
        RegisterSwPass__FPv(g_sw);
        UpdateHudWidgets__FP2DL(D_003D9E70);
        OpenFrame();
        if (!g_poverlay || FAnimatedOverlayDrawNormal__FPc(g_poverlay)) {
            RenderSw(g_sw);
            DrawSw(g_sw);
            UpdateRecyclable(D_003D9E70);
        }
        if (g_poverlay)
            DrawAnimatedOverlayFrame__FPv(g_poverlay);
        CloseFrame__Fv();
        g_cframe++;
    }
}
