/* func_001E0990: appends a RELAYCK_StepCmd1D command to the relay (oidGoal, oidActor); the script waits for it to complete. Called from the Splice binding func_00107C68. */
#include "relay.h"

void func_001E0990(RELAY *prelay, int oidGoal, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StepCmd1D, 0);
    prelaycmd->u.stepCmd1D.oidGoal = oidGoal;
    prelaycmd->u.stepCmd1D.oidActor = oidActor;
}
