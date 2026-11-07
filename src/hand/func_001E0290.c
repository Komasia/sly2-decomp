/* func_001E0290: appends a RELAYCK_BlockBegin command to the relay (oidLabel); asynchronous (the script does not wait for it). Called from the Splice binding func_00106A80. */
#include "relay.h"

void func_001E0290(RELAY *prelay, int oidLabel)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_BlockBegin, 1);
    prelaycmd->u.blockBegin.oidLabel = oidLabel;
}
