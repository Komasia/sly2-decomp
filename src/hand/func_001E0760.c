/* func_001E0760: appends a RELAYCK_GotoLabel command to the relay (oidLabel); asynchronous (the script does not wait for it). Called from the Splice binding func_001076A0. */
#include "relay.h"

void func_001E0760(RELAY *prelay, int oidLabel)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_GotoLabel, 1);
    prelaycmd->u.gotoLabel.oidLabel = oidLabel;
}
