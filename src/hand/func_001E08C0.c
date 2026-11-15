/* func_001E08C0: appends a RELAYCK_PipeTo command to the relay (oidTarget, gTolerance, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E08C0(RELAY *prelay, int oidTarget, int fAsync, int oidActor, float gTolerance)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_PipeTo, fAsync);
    prelaycmd->u.pipeTo.oidTarget = oidTarget;
    prelaycmd->u.pipeTo.gTolerance = gTolerance;
    prelaycmd->u.pipeTo.oidActor = oidActor;
}
