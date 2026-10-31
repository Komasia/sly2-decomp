/* func_001E0A60: appends a RELAYCK_StepCmd20 command to the relay (oidGoal, oidActor); the script waits for it to complete. Called from the Splice binding func_00107E70. */
#include "relay.h"

void func_001E0A60(RELAY *prelay, int oidGoal, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_StepCmd20, 0);
    prelaycmd->u.stepCmd20.oidGoal = oidGoal;
    prelaycmd->u.stepCmd20.oidActor = oidActor;
}
