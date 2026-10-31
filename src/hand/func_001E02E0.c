/* func_001E02E0: appends a RELAYCK_StopBlock command to the relay (oidLabel); asynchronous (the script does not wait for it). Called from the Splice binding func_00106B80. */
#include "relay.h"

void func_001E02E0(RELAY *prelay, int oidLabel)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_StopBlock, 1);
    prelaycmd->u.stopBlock.oidLabel = oidLabel;
}
