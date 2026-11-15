/* class: the title HUD widget D_003DA530 (its update, from the HUD update 0x1D9648): Start starts the game - from
 * the save chosen (D_002E65E0 +0xFD54, copied to +0xFD50) or a new game; Select (0x100, alone) opens the options;
 * with more than one language, Triangle (0x10) opens a language menu (screen object 0x5D6) listing the region's
 * languages, each choosing func_001DD8E0. */
#define BTN_START 0x800
#define BTN_SELECT 0x100
#define BTN_TRIANGLE 0x10
typedef struct { char pad[0x10B4]; int grfbtnHeld; } PAD;
typedef struct TITLE {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ PAD *pjoy;             /* the pad while the widget has the focus */
    /* 0x14 */ char pad14[0x24 - 0x14];
    /* 0x24 */ void *ploScreen;
} TITLE;
typedef struct { int ids; void (*pfn)(void); int lang; int pad[5]; } MENUENT;   /* a menu entry */
typedef struct { char pad[0xFD50]; void *xFD50; void *xFD54; } BIG;
extern BIG D_002E65E0;
extern char D_002E6550[];
extern struct G g_sw;
extern char D_003D9ED0[];
extern MENUENT D_003DA578[];
extern int D_002C35B8[];             /* each language's name text */
extern char D_002C35F0[];
void func_001DD8E0(void);
void func_001DA808(TITLE *);
int GrfbtnTakePressedJoy(PAD *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
int GrfbtnPressed__FP6JOYPS2Ui(PAD *, int);
void SetJoyPs2BtnHandled__FP6JOYPS2Ui(PAD *, int);
void AentOptions__FPv(int);
void func_001ACC38(void *, int);
void StartGameFromSave__FP2SW(void *);
void StartNewGameFromTitle__Fv(TITLE *);
int func_001A2C98(void);
void *PloFindSwNearest__FP2LO3OIDii(struct G *, int, int, int);
void FRegionLanguages__FPiPUi(int *, int **);
void *s1_memset(void *, int, int) asm("memset");
void PushPage__FP4MENUiPviUi(void *, int, MENUENT *, void *, void *);
void func_001DD920(TITLE *ptitle)
{
    void *pscreenLang;
    int clang;
    int *alang;
    int i;
    func_001DA808(ptitle);
    if (ptitle->ploScreen == 0)
        return;
    if (ptitle->pjoy == 0)
        return;
    if (GrfbtnTakePressedJoy(ptitle->pjoy, BTN_START)) {
        if ((D_002E65E0.xFD50 = D_002E65E0.xFD54) != 0) {
            func_001ACC38(D_002E6550, 1);
            StartGameFromSave__FP2SW(D_002E65E0.xFD50);
        } else {
            StartNewGameFromTitle__Fv(ptitle);
        }
        return;
    }
    if (GrfbtnPressed__FP6JOYPS2Ui(ptitle->pjoy, BTN_SELECT) && (ptitle->pjoy->grfbtnHeld & 0x108) == BTN_SELECT) {
        SetJoyPs2BtnHandled__FP6JOYPS2Ui(ptitle->pjoy, BTN_SELECT);
        AentOptions__FPv(0);
        return;
    }
    if (func_001A2C98() < 2)
        return;
    if (!GrfbtnTakePressedJoy(ptitle->pjoy, BTN_TRIANGLE))
        return;
    pscreenLang = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, 0x5D6, 0);
    if (pscreenLang == 0)
        return;
    FRegionLanguages__FPiPUi(&clang, &alang);
    for (i = 0; i < clang; i++) {
        int lang = alang[i];
        MENUENT *pent = &D_003DA578[i];
        s1_memset(pent, 0, sizeof(MENUENT));
        pent->lang = lang;
        pent->ids = D_002C35B8[lang];
        pent->pfn = func_001DD8E0;
    }
    PushPage__FP4MENUiPviUi(D_003D9ED0, clang, D_003DA578, pscreenLang, D_002C35F0);
}
