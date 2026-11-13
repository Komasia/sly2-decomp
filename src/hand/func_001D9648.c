extern struct CLOCK { float t; float dt; float g; } g_clock;
typedef struct { char pad[0x100C]; int x100C; } PAD;
extern int g_grfjoyt;
extern int g_grfusr;
extern PAD g_joy;
extern PAD D_002E0D00;
extern char D_003D9ED0[], D_003DA150[], D_003DA0F0[], D_002DDEC0[], D_00443740[], D_003D9E80[];
extern char D_003DA0C0[], D_003DA3C0[], D_002E6550[], D_002E65A0[], D_003DA4F0[], D_003DA530[];
void RemoveGrfusr__Fi(int);
int GrfbtnTakePressedJoy(PAD *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
void ClearJoyBtns__FP6JOYPS2Ui(PAD *, int);
int AentPause__FPv(int);
int FIsDlEmpty__FP2DL(void *);
void func_001AEEE0(void *);
void UpdateShop__FP2SW(void *);
void UpdateGadgetMenu__FP2SW(void *);
void func_0014BFF8(void *);
void UpdateWipe__FP4WIPE(void *);
void UpdateGauge__FP5GAUGE(void *);
void UpdatePrompt__FP6PROMPT(void *);
void UpdateJobHelp__FP2SW(void *);
void func_001ACCC8(void *);
void func_001ADEE8(void *);
void func_001DA808(void *);
void func_001DD920(void *);
void func_001D9648(void *pdl)
{
    PAD *pad;
    if (g_grfusr & 8) {
        if (g_clock.g == 0.0f || 0.1f < g_clock.t / g_clock.g)
            RemoveGrfusr__Fi(8);
    }
    if (g_grfjoyt & 2)
        pad = &g_joy;
    else
        pad = &D_002E0D00;
    if (GrfbtnTakePressedJoy(pad, 0x800)) {
        if (!AentPause__FPv(0))
            ClearJoyBtns__FP6JOYPS2Ui(pad, 0x800);
    } else if (g_grfjoyt & 2) {
        int r = FIsDlEmpty__FP2DL(pdl);
        int f = 0;
        if (pad->x100C == 1 && 5.0f <= g_clock.t)
            f = 1;
        if (r && f)
            AentPause__FPv(0);
    }
    func_001AEEE0(D_003D9ED0);
    UpdateShop__FP2SW(D_003DA150);
    UpdateGadgetMenu__FP2SW(D_003DA0F0);
    func_0014BFF8(D_002DDEC0);
    UpdateWipe__FP4WIPE(D_00443740);
    UpdateGauge__FP5GAUGE(D_003D9E80);
    UpdatePrompt__FP6PROMPT(D_003DA0C0);
    UpdateJobHelp__FP2SW(D_003DA3C0);
    func_001ACCC8(D_002E6550);
    func_001ADEE8(D_002E65A0);
    func_001DA808(D_003DA4F0);
    func_001DD920(D_003DA530);
}
