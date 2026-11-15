/* func_001E07D0: appends a RELAYCK_TeleportTo command to the relay (oidWhere, fAir, oidActor); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E07D0(RELAY *prelay, int oidWhere, int fAir, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_TeleportTo, 1);
    prelaycmd->u.teleportTo.oidWhere = oidWhere;
    prelaycmd->u.teleportTo.fAir = fAir;
    prelaycmd->u.teleportTo.oidActor = oidActor;
}
