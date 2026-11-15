#include "clock.h"
#include "h2_cmdlist.h"
struct GUARD { char pad[0xF80]; int nF80; char pad2[0xFD0 - 0xF84]; char moveref[4]; };   /* nF80: the guard's path follower kind (-1, 0, 1) */
/* JOBSCRIPT (include/h2_aijobs.h) */
struct JOBSCRIPT { char pad[0x10]; struct GUARD *pguard; int pad2; void *pchild; char pad3[0x1C]; CMD *pcmd; float tCmd; int fRunning; int pad4; float radFace; };
int FDone__11JOBPATHSTEP(void *pjob);
int func_0017CE30(void *pjob);
int func_0017D188(void *pjob);
int NArrived__7JOBGOTO(void *pjob);
int func_00174FB8(void *pjob);
void SetMoveHeading__FP7MOVEREF(void *pjob, float g);
void EndChildJob__FPP5AIJOB(void *pjob);
/* JOBSCRIPT::FRunning: whether the current command still runs: a path move until the path job is done, a go-to
 * until it arrives (then the guard turns to its heading), a wait until its time is up, a sub-job / animation until
 * its child is done; when it stops the child job is ended. */
// name: SafeHouse port (JOBSCRIPT::FRunning)
int FRunning__9JOBSCRIPT(struct JOBSCRIPT *pjob) {
    if (!pjob->fRunning) return 0;
    switch (pjob->pcmd->op) {
    case CMDOP_Path:
        switch (pjob->pguard->nF80) {
        case -1:
            if (FDone__11JOBPATHSTEP(pjob->pchild)) pjob->fRunning = 0;
            break;
        case 0:
            if (func_0017CE30(pjob->pchild)) pjob->fRunning = 0;
            break;
        case 1:
            if (func_0017D188(pjob->pchild)) pjob->fRunning = 0;
            break;
        }
        break;
    case CMDOP_Goto:
        if (NArrived__7JOBGOTO(pjob->pchild)) {
            pjob->fRunning = 0;
            SetMoveHeading__FP7MOVEREF(pjob->pguard->moveref, pjob->radFace);
        }
        break;
    case CMDOP_Wait:
        if (*(float *)&pjob->pcmd->n8 < g_clock.t - pjob->tCmd) pjob->fRunning = 0;
        break;
    case CMDOP_Job: case CMDOP_Anim:
        if (func_00174FB8(pjob->pchild)) pjob->fRunning = 0;
        break;
    }
    if (!pjob->fRunning) EndChildJob__FPP5AIJOB(&pjob->pchild);
    return pjob->fRunning;
}
