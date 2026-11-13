/* SetEpMode: the episode menu's mode and sub-mode: leaving mode 0 auto-saves (HudAutoSave on g_save, D_002E65E0),
 * leaving 4 / 6 makes the next entry the current one, leaving 2 resets the hint; entering 2 shows the hint anew.
 * The screen object is stopped (no show / idle / hide parts, the timer 1, state 1), the mode's time is the real
 * clock's, and the current part shown (vt slot 49, ShowScreenObj). Layout: SafeHouse port (frontend.cpp EPMENU,
 * screenrt.h). */
#include "clock.h"
#include "vtbl.h"

struct EPMENU {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;
    /* 0x010 */ char pad10[0x70 - 0x10];
    /* 0x070 */ int idShow;      /* SafeHouse: the show / idle / hide parts */
    /* 0x074 */ int idIdle;
    /* 0x078 */ int idHide;
    /* 0x07c */ char pad7C[0x110 - 0x7c];
    /* 0x110 */ int cur;         /* field: SafeHouse port */
    /* 0x114 */ int next;        /* field: SafeHouse port */
    /* 0x118 */ char pad118[0x11c - 0x118];
    /* 0x11c */ int mode;        /* field: SafeHouse port */
    /* 0x120 */ int sub;         /* field: SafeHouse port */
    /* 0x124 */ float t124;      /* field: SafeHouse port */
};
extern char D_002E65E0[];   /* g_save */
void HudAutoSave__FP4SAVEi(void *psave, int n);
void SetHint__FP6EPMENUi(struct EPMENU *pepmenu, int n);
void SetTimerTimers__FP5TIMER6TIMERS(struct EPMENU *pepmenu, int timers);
void SetState__FP8SCREENRTi(struct EPMENU *pepmenu, int state);
int IdPartCur__FP6EPMENU(struct EPMENU *pepmenu);

// name: SafeHouse port (SetEpMode)
void SetEpMode__FP6EPMENUii(struct EPMENU *pepmenu, int mode, int sub)
{
    int modeOld = pepmenu->mode;
    if (modeOld != mode || pepmenu->sub != sub) {
        int id;
        switch (modeOld) {
        case 0:
            HudAutoSave__FP4SAVEi(D_002E65E0, 1);
            break;
        case 4:
        case 6: {
            int next = pepmenu->next;
            pepmenu->next = -1;
            pepmenu->cur = next;
            break;
        }
        case 2:
            SetHint__FP6EPMENUi(pepmenu, 0);
            break;
        }
        if (mode == 2) {
            SetHint__FP6EPMENUi(pepmenu, -1);
            SetHint__FP6EPMENUi(pepmenu, 0);
        }
        pepmenu->idIdle = -1;
        pepmenu->idShow = -1;
        pepmenu->idHide = -1;
        SetTimerTimers__FP5TIMER6TIMERS(pepmenu, 1);
        SetState__FP8SCREENRTi(pepmenu, 1);
        pepmenu->mode = mode;
        pepmenu->sub = sub;
        pepmenu->t124 = g_clock.tReal;
        id = IdPartCur__FP6EPMENU(pepmenu);
        if (id != -1) {
            VTENT *pvte = &pepmenu->pvt[0x188 / 8];
            ((void (*)(void *, int))pvte->pfn)(VT_THIS(pepmenu, pvte), id);
        }
    }
}
