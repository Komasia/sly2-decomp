/* func_001E09D0: appends a RELAYCK_StepCmd1E command to the relay (oidA, oidB, oidActor); the script waits for it to complete. */
#include "relay.h"

void func_001E09D0(RELAY *prelay, int oidA, int oidB, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StepCmd1E, 0);
    prelaycmd->u.stepCmd1E.oidA = oidA;
    prelaycmd->u.stepCmd1E.oidB = oidB;
    prelaycmd->u.stepCmd1E.oidActor = oidActor;
}
