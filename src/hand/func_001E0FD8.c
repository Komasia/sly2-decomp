/* func_001E0FD8: appends a RELAYCK_ShowPart command to the relay (oidAseg, oidPart); asynchronous (the script does not wait for it). Called from the Splice binding func_00108B50. */
#include "relay.h"

void func_001E0FD8(RELAY *prelay, int oidAseg, int oidPart)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ShowPart, 1);
    prelaycmd->u.showPart.oidAseg = oidAseg;
    prelaycmd->u.showPart.oidPart = oidPart;
}
