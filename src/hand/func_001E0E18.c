/* func_001E0E18: appends a RELAYCK_Respawn command to the relay (oidSpot, nUnk5, nUnk6, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E0E18(RELAY *prelay, int oidSpot, int nUnk5, int nUnk6, int fAsync, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Respawn, fAsync);
    prelaycmd->u.respawn.oidSpot = oidSpot;
    prelaycmd->u.respawn.nUnk5 = nUnk5;
    prelaycmd->u.respawn.nUnk6 = nUnk6;
    prelaycmd->u.respawn.oidActor = oidActor;
}
