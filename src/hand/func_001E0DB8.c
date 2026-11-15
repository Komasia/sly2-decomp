/* func_001E0DB8: appends a RELAYCK_StepCmd29 command to the relay (oidTarget, gUnk5, gArrive, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E0DB8(RELAY *prelay, int oidTarget, int fAsync, int oidActor, float gUnk5, float gArrive)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StepCmd29, fAsync);
    prelaycmd->u.stepCmd29.oidTarget = oidTarget;
    prelaycmd->u.stepCmd29.gUnk5 = gUnk5;
    prelaycmd->u.stepCmd29.gArrive = gArrive;
    prelaycmd->u.stepCmd29.oidActor = oidActor;
}
