/* func_001E0F98: appends a RELAYCK_ClearPartFlag command to the relay (oidAseg, oidPart); asynchronous (the script does not wait for it). Called from the Splice binding func_00108AA8. */
#include "relay.h"

void func_001E0F98(RELAY *prelay, int oidAseg, int oidPart)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ClearPartFlag, 1);
    prelaycmd->u.clearPartFlag.oidAseg = oidAseg;
    prelaycmd->u.clearPartFlag.oidPart = oidPart;
}
