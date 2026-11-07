/* func_001E0530: appends a RELAYCK_FireRelay command to the relay (oidRelay, oidFirer); fAsync from the caller. Called from the Splice binding func_001070E0. */
#include "relay.h"

void func_001E0530(RELAY *prelay, int oidRelay, int oidFirer, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_FireRelay, fAsync);
    prelaycmd->u.fireRelay.oidRelay = oidRelay;
    prelaycmd->u.fireRelay.oidFirer = oidFirer;
}
