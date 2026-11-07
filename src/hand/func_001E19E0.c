/* func_001E19E0: appends a RELAYCK_SetSsgGoal command to the relay (oidStep, oidSsg); fAsync from the caller. Called from the Splice binding func_0010A380. */
#include "relay.h"

void func_001E19E0(RELAY *prelay, int oidStep, int oidSsg, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_SetSsgGoal, fAsync);
    prelaycmd->u.setSsgGoal.oidStep = oidStep;
    prelaycmd->u.setSsgGoal.oidSsg = oidSsg;
}
