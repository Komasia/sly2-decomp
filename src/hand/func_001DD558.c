#include "clock.h"
/* class: JOBHELP, the Job Help HUD widget (its vtable entry 14, as SetShopDir): the stick's direction (eighths of a
 * turn from the right, -1 none) changes: right opens the selected job's goals (page 1, when there are rows), left
 * goes back to the jobs (page 0); up-ish (1..3) / down-ish (5..7) select the row above / below (sound 0x35). */
#define DIR_Right 0
#define DIR_Left 4
typedef struct JOBHELP {              /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad[0x28];
    /* 0x028 */ int dir;
    /* 0x02c */ float tDir;
    /* 0x030 */ char pad30[0x48 - 0x30];
    /* 0x048 */ int crow;
    /* 0x04c */ char pad4c[0x118 - 0x4C];
    /* 0x118 */ int isel;
} JOBHELP;
void SetJobHelpPage__FPvi(JOBHELP *, int);
void func_001DCE90(JOBHELP *, int);
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void func_001DD558(JOBHELP *pjobhelp, unsigned int dir)
{
    if (dir == pjobhelp->dir)
        return;
    pjobhelp->dir = dir;
    pjobhelp->tDir = g_clock.tReal;
    switch (dir) {
    case DIR_Right:
        if (pjobhelp->crow)
            SetJobHelpPage__FPvi(pjobhelp, 1);
        break;
    case DIR_Left:
        SetJobHelpPage__FPvi(pjobhelp, 0);
        break;
    case 1:
    case 2:
    case 3:
        if (pjobhelp->isel > 0) {
            func_001DCE90(pjobhelp, pjobhelp->isel - 1);
            SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        }
        break;
    case 5:
    case 6:
    case 7:
        if (pjobhelp->isel < pjobhelp->crow - 1) {
            func_001DCE90(pjobhelp, pjobhelp->isel + 1);
            SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        }
        break;
    }
}
