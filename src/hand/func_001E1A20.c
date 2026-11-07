/* func_001E1A20: appends a RELAYCK_ResetStepGoal command to the relay (oidStep, oidUnk5); asynchronous (the script does not wait for it). Called from the Splice binding func_0010A438. */
#include "relay.h"

void func_001E1A20(RELAY *prelay, int oidStep, int oidUnk5)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ResetStepGoal, 1);
    prelaycmd->u.resetStepGoal.oidStep = oidStep;
    prelaycmd->u.resetStepGoal.oidUnk5 = oidUnk5;
}
