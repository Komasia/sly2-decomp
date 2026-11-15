/* func_001E0CB8: appends a RELAYCK_FollowPath command to the relay (oidPath, nPathMode, nUnk6, gUnk7, oidActor, idClip); the script waits for it to complete. */
#include "relay.h"

void func_001E0CB8(RELAY *prelay, int oidPath, int nPathMode, int nUnk6, int oidActor, int idClip, float gUnk7)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_FollowPath, 0);
    prelaycmd->u.followPath.oidPath = oidPath;
    prelaycmd->u.followPath.nPathMode = nPathMode;
    prelaycmd->u.followPath.nUnk6 = nUnk6;
    prelaycmd->u.followPath.gUnk7 = gUnk7;
    prelaycmd->u.followPath.oidActor = oidActor;
    prelaycmd->u.followPath.idClip = idClip;
}
