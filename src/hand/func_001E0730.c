/* func_001E0730: appends a RELAYCK_Label command to the relay (oidLabel); asynchronous (the script does not wait for it). Called from the Splice binding func_00107618. */
#include "relay.h"

void func_001E0730(RELAY *prelay, int oidLabel)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Label, 1);
    prelaycmd->u.label.oidLabel = oidLabel;
}
