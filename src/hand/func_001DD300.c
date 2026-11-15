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
/* SetJobHelpPage (SafeHouse shop.cpp): show Job Help at page 0 (the jobs, 10 rows) or 1 (the selected job's goals,
 * 4 rows; the current job when none is selected), or close it (-1; also without a screen object). Opening pauses the
 * game and shows the widget; closing resumes, hides it and drops the part handles. A page sets its screen object's
 * title parts (+0x70..+0x78) and restarts it; then the rows are rebuilt and the stick direction reset. */
typedef struct { void *pv; int idRow; int idDone; } JOBHELPROW;   /* the job / task and its part handles */
typedef struct JOBHELP {              /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad0[0xC];
    /* 0x00c */ VTENT *vt;
    /* 0x010 */ char pad10[0x24 - 0x10];
    /* 0x024 */ SUB *pscreen;
    /* 0x028 */ char pad28[0x40 - 0x28];
    /* 0x040 */ int page;
    /* 0x044 */ float tPage;
    /* 0x048 */ int crow;
    /* 0x04c */ JOBHELPROW arow[1];
    /* 0x058 */ char pad58[0x10C - 0x58];
    /* 0x10c */ int crowMax;
    /* 0x110 */ void *pjob;           /* the job shown on page 1 */
    /* 0x114 */ int fFromJobs;
    /* 0x118 */ int isel;
    /* 0x11c */ int idPrompt;
    /* 0x120 */ int idUp;
    /* 0x124 */ int idDown;
} JOBHELP;
#include "clock.h"
extern char g_sw[];
extern void *D_003E0F9C;             /* the current job */
void PauseGame__FP9GAMEPAUSEi(void *, int);
void ResumeGame__FP9GAMEPAUSEi(void *, int);
void SetState__FP8SCREENRTi(SUB *, int);
void SetTimerTimers(SUB *, int) asm("SetTimerTimers__FP5TIMER6TIMERS");
void BuildJobHelp__FPv(JOBHELP *);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]))
// name: SafeHouse port (SetJobHelpPage)
void SetJobHelpPage__FPvi(JOBHELP *pjobhelp, int page)
{
    int pageOld;
    if (!pjobhelp->pscreen)
        page = -1;
    if (page == pjobhelp->page)
        return;
    if (pjobhelp->page == -1) {
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pjobhelp, 10);
    }
    pageOld = pjobhelp->page;
    pjobhelp->page = page;
    pjobhelp->tPage = g_clock.tReal;
    switch (page) {
    case -1:
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pjobhelp, 11);
        if (pjobhelp->pscreen->x58 > 0)
            SetTimerTimers(pjobhelp->pscreen, 1);
        pjobhelp->idPrompt = page;
        pjobhelp->idUp = page;
        pjobhelp->idDown = page;
        break;
    case 0:
        pjobhelp->crowMax = 0xA;
        pjobhelp->pscreen->x70 = 0x4E3;
        pjobhelp->pscreen->x78 = 0x4E2;
        if (pageOld == 1)
            pjobhelp->pscreen->x74 = 0x4E8;
        else
            pjobhelp->pscreen->x74 = 0x4E1;
        if (pjobhelp->pscreen->x58) {
            SetState__FP8SCREENRTi(pjobhelp->pscreen, 1);
            SetTimerTimers(pjobhelp->pscreen, 2);
            VCALL(pjobhelp->pscreen, 16);
        }
        break;
    case 1: {
        int isel = pjobhelp->isel;
        if (isel >= 0 && isel < pjobhelp->crow)
            pjobhelp->pjob = pjobhelp->arow[isel].pv;
        else
            pjobhelp->pjob = D_003E0F9C;
        pjobhelp->fFromJobs = (pageOld == 0);
        pjobhelp->crowMax = 4;
        pjobhelp->pscreen->x70 = 0x4E6;
        pjobhelp->pscreen->x78 = 0x4E5;
        if (pageOld == 0)
            pjobhelp->pscreen->x74 = 0x4E7;
        else
            pjobhelp->pscreen->x74 = 0x4E4;
        if (pjobhelp->pscreen->x58) {
            SetState__FP8SCREENRTi(pjobhelp->pscreen, 1);
            SetTimerTimers(pjobhelp->pscreen, 2);
            VCALL(pjobhelp->pscreen, 16);
        }
        break;
    }
    }
    BuildJobHelp__FPv(pjobhelp);
    ((void (*)(void *, int))pjobhelp->vt[14].pfn)(VT_THIS(pjobhelp, &pjobhelp->vt[14]), -1);
}
