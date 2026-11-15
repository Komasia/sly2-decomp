/* StartScptImpl: fires the relay with ploFirer as the firer, unless it is firing already: sends the Splice event 5
 * (fired, vt slot 3), appends the closing BlockEnd command if still due, starts a script (JSG) at the first command and
 * runs it. If scripts are left running, the relay goes on the update list (func_001A6CA8 + GRFUPD_Update) unless it
 * already updates. Each step re-checks fFiring, since the event or the script may stop the relay. */
#include "relay.h"
#include "h3_update.h"
#define SPLICEEVENT_Fired 5
typedef void (*PFNSPLICEEVENT)(void *plo, int event, int, int, int, int);
void func_001E02C0(RELAY *prelay);            /* append a BlockEnd command */
void *PrunNew__FP2LOPvP3RUN(RELAY *prelay, RELAYCMD *prelaycmdFirst, int);
void RunRun__FP4PRUN(void *pjsg);
int FIsDlEmpty__FP2DL(DL *);
void StopScptImpl__FP2LO(RELAY *);
void func_001A6CA8(RELAY *, int);             /* update list: 1 add, 2 remove (SafeHouse SetLoSt) */
// name: SafeHouse port (StartScptImpl)
void StartScptImpl__FP2LOi(RELAY *prelay, LO *ploFirer)
{
    int grf;
    if (prelay->fFiring)
        return;
    prelay->ploFirer = ploFirer;
    prelay->fFiring = 1;
    prelay->fUpdating = 0;
    ((PFNSPLICEEVENT)prelay->lo.pvt[3].pfn)(VT_THIS(prelay, &prelay->lo.pvt[3]), SPLICEEVENT_Fired, 0, 0, 0, 0);
    if (!prelay->fFiring)
        return;
    if (prelay->fAppendEnd) {
        func_001E02C0(prelay);
        prelay->fAppendEnd = 0;
    }
    RunRun__FP4PRUN(PrunNew__FP2LOPvP3RUN(prelay, prelay->arelaycmd, 0));
    if (!prelay->fFiring)
        return;
    if (FIsDlEmpty__FP2DL(&prelay->dlJsg)) {
        StopScptImpl__FP2LO(prelay);
        return;
    }
    grf = prelay->lo.grfUnk40;
    if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags)
        grf = *(int *)grf;
    if (grf & GRFUPD_Update)
        return;
    func_001A6CA8(prelay, 1);
    if ((prelay->lo.grfUnk40 ^ GRFUPD_Flags) & GRFUPD_Flags)
        *(int *)prelay->lo.grfUnk40 |= GRFUPD_Update;
    else
        prelay->lo.grfUnk40 |= GRFUPD_Update;
    prelay->fUpdating = 1;
}
