/* func_001E0AA0: appends a RELAYCK_StepCmd21 command to the relay (oidGoal, oidActor); the script waits for it to complete. Called from the Splice binding func_00107F18. */
#include "relay.h"

void func_001E0AA0(RELAY *prelay, int oidGoal, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StepCmd21, 0);
    prelaycmd->u.stepCmd21.oidGoal = oidGoal;
    prelaycmd->u.stepCmd21.oidActor = oidActor;
}
