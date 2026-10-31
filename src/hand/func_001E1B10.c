/* func_001E1B10: appends a RELAYCK_Unk5A command to the relay (oidShip, oidActor, nUnk6); fAsync from the caller. Called from the Splice binding func_0010A6D8. */
#include "relay.h"

void func_001E1B10(RELAY *prelay, int oidShip, int oidActor, int fAsync)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk5A, fAsync);
    prelaycmd->u.unk5A.oidShip = oidShip;
    prelaycmd->u.unk5A.oidActor = oidActor;
    prelaycmd->u.unk5A.nUnk6 = 0;
}
