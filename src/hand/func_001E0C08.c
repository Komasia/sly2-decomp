/* func_001E0C08: appends a RELAYCK_GoTo command to the relay (oidTarget, uRun, gArrive, oidActor, idClip); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E0C08(RELAY *prelay, int oidTarget, int fAsync, int oidActor, int idClip, float uRun, float gArrive)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_GoTo, fAsync);
    prelaycmd->u.goTo.oidTarget = oidTarget;
    prelaycmd->u.goTo.uRun = uRun;
    prelaycmd->u.goTo.gArrive = gArrive;
    prelaycmd->u.goTo.oidActor = oidActor;
    prelaycmd->u.goTo.idClip = idClip;
    prelaycmd->u.goTo.fUnk9 = 0;
}
