/* func_001E0AE0: appends a RELAYCK_StepCmd22 command to the relay (oidTarget, nMode, nUnk6, oidActor); the script waits for it to complete. */
#include "relay.h"

void func_001E0AE0(RELAY *prelay, int oidTarget, int nMode, int nUnk6, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StepCmd22, 0);
    prelaycmd->u.stepCmd22.oidTarget = oidTarget;
    prelaycmd->u.stepCmd22.nMode = nMode;
    prelaycmd->u.stepCmd22.nUnk6 = nUnk6;
    prelaycmd->u.stepCmd22.oidActor = oidActor;
}
