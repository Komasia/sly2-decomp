#include "vtbl.h"
typedef struct SUB {
    char pad0[0xC];
    VTENT *vt;
    char pad10[0x58 - 0x10];
    int x58;
    char pad5c[0x70 - 0x5C];
    int x70;
    int x74;
    int x78;
} SUB;
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp SHOP) */
    char pad0[0xC];
    VTENT *vt;
    char pad10[0x24 - 0x10];
    SUB *pscreen;
    char pad28[0x40 - 0x28];
    int page;
    float tPage;
    char pad48[0x25C - 0x48];
    int idPrompt;
    int idUp;
    int idDown;
} SHOP;
#include "clock.h"
extern char g_sw[];
void SetClockFactor__FP5CLOCKif(struct CLOCK *, float, int);
void PauseGame__FP9GAMEPAUSEi(void *, int);
void ResumeGame__FP9GAMEPAUSEi(void *, int);
void SetState__FP8SCREENRTi(SUB *, int);
void SetTimerTimers(SUB *, int) asm("SetTimerTimers__FP5TIMER6TIMERS");
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void BuildShopList__FP4SHOP(SHOP *);
void SelectShopRow__FP4SHOPi(SHOP *, int);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]))
/* SetShopPage (SafeHouse shop.cpp: 0x1DC260(0x3DA150, page)): show the shop at page 0 (buy) or 1 (sell), or close
 * it (-1; also without a screen object). Opening stops the clock, pauses the game and shows the widget; closing
 * hides the screen object and the widget, resumes and drops the part handles. A page sets its title / tab parts
 * (0x4D4..0x4D6 or 0x49B..0x49D) and switches with a slide when changing pages; then the rows are rebuilt, the first
 * selected, and the stick direction reset (vtable entry 14). */
void func_001DC260(SHOP *pshop, int page)
{
    int pageOld;
    if (!pshop->pscreen)
        page = -1;
    if (page == pshop->page)
        return;
    if (pshop->page == -1) {
        SetClockFactor__FP5CLOCKif(&g_clock, 0.0f, 0);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pshop, 10);
        SetState__FP8SCREENRTi(pshop->pscreen, 1);
    }
    pageOld = pshop->page;
    pshop->page = page;
    pshop->tPage = g_clock.tReal;
    switch (page) {
    case -1:
        VCALL(pshop->pscreen, 50);
        SetClockFactor__FP5CLOCKif(&g_clock, 1.0f, 0);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pshop, 11);
        if (pshop->pscreen->x58 > 0)
            SetTimerTimers(pshop->pscreen, 1);
        pshop->idPrompt = page;
        pshop->idUp = page;
        pshop->idDown = page;
        break;
    case 0:
        pshop->pscreen->x74 = 0x4D4;
        pshop->pscreen->x70 = 0x4D5;
        pshop->pscreen->x78 = 0x4D6;
        if (pageOld == 1) {
            SetState__FP8SCREENRTi(pshop->pscreen, 1);
            SetState__FP8SCREENRTi(pshop->pscreen, 2);
        } else {
            SetTimerTimers(pshop->pscreen, 2);
        }
        SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        break;
    case 1:
        pshop->pscreen->x74 = 0x49B;
        pshop->pscreen->x70 = 0x49C;
        pshop->pscreen->x78 = 0x49D;
        if (pageOld == 0) {
            SetState__FP8SCREENRTi(pshop->pscreen, 1);
            SetState__FP8SCREENRTi(pshop->pscreen, 2);
        } else {
            SetTimerTimers(pshop->pscreen, 2);
        }
        SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        break;
    }
    BuildShopList__FP4SHOP(pshop);
    SelectShopRow__FP4SHOPi(pshop, 0);
    ((void (*)(void *, int))pshop->vt[14].pfn)(VT_THIS(pshop, &pshop->vt[14]), -1);
}
