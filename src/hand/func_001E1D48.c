/* FinishRunPending: if the script's pending command is done, clears it (SetRunPending(0, 0)) - except a StepCmd1D
 * with a goal object, which stays pending. */
#include "relay.h"
int FCmdDone__FP3RUNP7SCPTCMD(JSG *pjsg, RELAYCMD *prelaycmd);
void SetRunPending__FP3RUNiP2LO(JSG *pjsg, int ic, LO *plo);
// name: SafeHouse port (FinishRunPending)
void FinishRunPending__FP3RUN(JSG *pjsg)
{
    if (pjsg->prelaycmdJt && FCmdDone__FP3RUNP7SCPTCMD(pjsg, pjsg->prelaycmdJt)) {
        int fClear = 1;
        if (pjsg->prelaycmdJt->relayck == RELAYCK_StepCmd1D) fClear = (pjsg->prelaycmdJt->u.stepCmd1D.oidGoal == -1);
        if (fClear) SetRunPending__FP3RUNiP2LO(pjsg, 0, 0);
    }
}
