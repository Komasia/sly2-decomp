/* func_001E0420: appends a RELAYCK_StopRelay command to the relay (oidRelay); asynchronous (the script does not wait for it). Called from the Splice binding func_00106DF8. */
#include "relay.h"

void func_001E0420(RELAY *prelay, int oidRelay)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StopRelay, 1);
    prelaycmd->u.stopRelay.oidRelay = oidRelay;
}
