/* func_001E0A20: appends a RELAYCK_StepCmd1F command to the relay (oidGoal, oidActor); the script waits for it to complete. Called from the Splice binding func_00107DC8. */
#include "relay.h"

void func_001E0A20(RELAY *prelay, int oidGoal, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_StepCmd1F, 0);
    prelaycmd->u.stepCmd1F.oidGoal = oidGoal;
    prelaycmd->u.stepCmd1F.oidActor = oidActor;
}
