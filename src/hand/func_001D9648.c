/* class: the HUD's widget list (SafeHouse hudwidget.cpp: "orig 0x1D9648", the HUD widgets' update): per frame - user
 * flag 8 is dropped when g_clock.rt is 0 or t / rt passes 0.1; Start (0x800) on the active pad pauses (the press is
 * cleared when pausing is refused); with the first pad active and the HUD list empty, a pad in state 1 (+0x100C)
 * pauses once t reaches 5 s; then every HUD widget is updated. */
#include "clock.h"
#define BTN_START 0x800
#define JOYT_FIRST 2                  /* g_grfjoyt bit: use g_joy (else the other pad, D_002E0D00) */
typedef struct { char pad[0x100C]; int joys; } PAD;   /* joys: the pad state (SafeHouse joy.h: 3 ready) */
extern int g_grfjoyt;
extern int g_grfusr;
extern PAD g_joy;
extern PAD D_002E0D00;
extern char D_003D9ED0[];             /* the menu */
extern char D_003DA150[];             /* the shop */
extern char D_003DA0F0[];             /* the gadget menu */
extern char D_002DDEC0[], D_00443740[];   /* the wipe's owner, the wipe */
extern char D_003D9E80[];             /* the gauge */
extern char D_003DA0C0[];             /* the prompt */
extern char D_003DA3C0[];             /* the job help */
extern char D_002E6550[], D_002E65A0[], D_003DA4F0[], D_003DA530[];
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
    PAD *pjoy;
    if (g_grfusr & 8) {
        if (g_clock.rt == 0.0f || 0.1f < g_clock.t / g_clock.rt)
            RemoveGrfusr__Fi(8);
    }
    if (g_grfjoyt & JOYT_FIRST)
        pjoy = &g_joy;
    else
        pjoy = &D_002E0D00;
    if (GrfbtnTakePressedJoy(pjoy, BTN_START)) {
        if (!AentPause__FPv(0))
            ClearJoyBtns__FP6JOYPS2Ui(pjoy, BTN_START);
    } else if (g_grfjoyt & JOYT_FIRST) {
        int fEmpty = FIsDlEmpty__FP2DL(pdl);
        int fState1 = 0;
        if (pjoy->joys == 1 && 5.0f <= g_clock.t)
            fState1 = 1;
        if (fEmpty && fState1)
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
