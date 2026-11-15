/* func_001E13B8: appends a RELAYCK_StartJtMode command to the relay (oidActor, oidStep, oidUnk6); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E13B8(RELAY *prelay, int oidActor, int oidStep, int oidUnk6, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StartJtMode, fAsync);
    prelaycmd->u.startJtMode.oidActor = oidActor;
    prelaycmd->u.startJtMode.oidStep = oidStep;
    prelaycmd->u.startJtMode.oidUnk6 = oidUnk6;
}
