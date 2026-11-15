/* class: JOBHELP, the Job Help HUD widget (SafeHouse shop.cpp): reset its state - no page (its time the real time),
 * no prompt / up / down handles (+0x11C..+0x124, as the shop's +0x25C..+0x264). */
#include "clock.h"
struct JOBHELP {                      /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int page;             /* 0 the jobs, 1 a job's goals */
    /* 0x044 */ float tPage;
    /* 0x048 */ char pad48[0x11C - 0x48];
    /* 0x11c */ int idPrompt;
    /* 0x120 */ int idUp;
    /* 0x124 */ int idDown;
};

void func_001DCD08(struct JOBHELP *pjobhelp)
{
    pjobhelp->page = -1;
    pjobhelp->tPage = g_clock.tReal;
    pjobhelp->idPrompt = -1;
    pjobhelp->idUp = -1;
    pjobhelp->idDown = -1;
}
