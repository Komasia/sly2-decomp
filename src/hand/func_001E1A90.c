/* func_001E1A90: appends a RELAYCK_Unk58 command to the relay (oidShip, oidActor); fAsync from the caller. Called from the Splice binding func_0010A568. */
#include "relay.h"

void func_001E1A90(RELAY *prelay, int oidShip, int oidActor, int fAsync)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk58, fAsync);
    prelaycmd->u.unk58.oidShip = oidShip;
    prelaycmd->u.unk58.oidActor = oidActor;
}
