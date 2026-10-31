/* func_001E0F58: appends a RELAYCK_SetPartFlag command to the relay (oidAseg, oidPart); asynchronous (the script does not wait for it). Called from the Splice binding func_00108A00. */
#include "relay.h"

void func_001E0F58(RELAY *prelay, int oidAseg, int oidPart)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetPartFlag, 1);
    prelaycmd->u.setPartFlag.oidAseg = oidAseg;
    prelaycmd->u.setPartFlag.oidPart = oidPart;
}
