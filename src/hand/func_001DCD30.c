#include "vtbl.h"
typedef struct VT { VTENT a[32]; } VT;
typedef struct { char pad[0xC]; VT *vt; char pad10[0x58 - 0x10]; int x58; } W;
/* UpdateJobHelp (SafeHouse shop.cpp): while Job Help is open and has the pad: wait for its screen object to open
 * (then start its timers, vtable entry 16); Start closes it; on the jobs page Triangle closes and the face buttons
 * (0xF0) open the selected job's goals; on the goals page Triangle closes (unless it came from the jobs page) and
 * the face buttons go back; then the stick and the look. */
#define BTN_START 0x800
#define BTN_TRIANGLE 0x10
#define GRFBTN_FACE 0xF0
typedef struct JOBHELP {              /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad[0x10];
    /* 0x010 */ void *pjoy;
    /* 0x014 */ char pad14[0x24 - 0x14];
    /* 0x024 */ W *pw;                /* the screen object */
    /* 0x028 */ char pad28[0x40 - 0x28];
    /* 0x040 */ int page;             /* -1 closed, 0 the jobs, 1 a job's goals */
    /* 0x044 */ char pad44[4];
    /* 0x048 */ int crow;
    /* 0x04c */ char pad4c[0x114 - 0x4C];
    /* 0x114 */ int fFromJobs;
} JOBHELP;
void func_001DA808(JOBHELP *);
int func_002127C8(void);
void SetState__FP8SCREENRTi(W *, int);
void SetTimerTimers(W *, int) asm("SetTimerTimers__FP5TIMER6TIMERS");
int GrfbtnTakePressedJoy(void *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
void SetJobHelpPage__FPvi(JOBHELP *, int);
void UpdateShopStick__FP4SHOP(JOBHELP *);
void UpdateJobHelpLook__FPv(JOBHELP *);
// name: SafeHouse port (UpdateJobHelp)
void UpdateJobHelp__FP2SW(JOBHELP *pjobhelp)
{
    func_001DA808(pjobhelp);
    if (pjobhelp->page == -1)
        return;
    if (pjobhelp->pjoy == 0)
        return;
    if (pjobhelp->pw->x58 == 0) {
        if (!func_002127C8())
            return;
        SetState__FP8SCREENRTi(pjobhelp->pw, 1);
        SetTimerTimers(pjobhelp->pw, 2);
        ((void (*)(void *))pjobhelp->pw->vt->a[16].pfn)(VT_THIS(pjobhelp->pw, &pjobhelp->pw->vt->a[16]));
    }
    if (GrfbtnTakePressedJoy(pjobhelp->pjoy, BTN_START)) {
        SetJobHelpPage__FPvi(pjobhelp, -1);
        return;
    }
    switch (pjobhelp->page) {
    case 0:
        if (GrfbtnTakePressedJoy(pjobhelp->pjoy, BTN_TRIANGLE)) {
            SetJobHelpPage__FPvi(pjobhelp, -1);
            return;
        }
        if (pjobhelp->crow && GrfbtnTakePressedJoy(pjobhelp->pjoy, GRFBTN_FACE)) {
            SetJobHelpPage__FPvi(pjobhelp, 1);
            return;
        }
        break;
    case 1:
        if (!pjobhelp->fFromJobs && GrfbtnTakePressedJoy(pjobhelp->pjoy, BTN_TRIANGLE)) {
            SetJobHelpPage__FPvi(pjobhelp, -1);
            return;
        }
        if (GrfbtnTakePressedJoy(pjobhelp->pjoy, GRFBTN_FACE)) {
            SetJobHelpPage__FPvi(pjobhelp, 0);
            return;
        }
        break;
    }
    UpdateShopStick__FP4SHOP(pjobhelp);
    UpdateJobHelpLook__FPv(pjobhelp);
}
