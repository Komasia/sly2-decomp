/* func_001E0E78: appends a RELAYCK_LaunchTo command to the relay (oidTarget, gUnk5, gUnk6, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E0E78(RELAY *prelay, int oidTarget, int fAsync, int oidActor, float gUnk5, float gUnk6)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_LaunchTo, fAsync);
    prelaycmd->u.launchTo.oidTarget = oidTarget;
    prelaycmd->u.launchTo.gUnk5 = gUnk5;
    prelaycmd->u.launchTo.gUnk6 = gUnk6;
    prelaycmd->u.launchTo.oidActor = oidActor;
}
