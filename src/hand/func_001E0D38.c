/* func_001E0D38: appends a RELAYCK_WalkTo command to the relay (oidTarget, gUnk5, nUnk6, gUnk7, oidActor, idClip); the script waits for it to complete. */
#include "relay.h"

void func_001E0D38(RELAY *prelay, int oidTarget, float gUnk5, int nUnk6, float gUnk7, int oidActor, int idClip)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_WalkTo, 0);
    prelaycmd->u.walkTo.oidTarget = oidTarget;
    prelaycmd->u.walkTo.gUnk5 = gUnk5;
    prelaycmd->u.walkTo.nUnk6 = nUnk6;
    prelaycmd->u.walkTo.gUnk7 = gUnk7;
    prelaycmd->u.walkTo.oidActor = oidActor;
    prelaycmd->u.walkTo.idClip = idClip;
}
