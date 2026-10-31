/* func_001E1018: appends a RELAYCK_HidePart command to the relay (oidAseg, oidPart); asynchronous (the script does not wait for it). Called from the Splice binding func_00108BF8. */
#include "relay.h"

void func_001E1018(RELAY *prelay, int oidAseg, int oidPart)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_HidePart, 1);
    prelaycmd->u.hidePart.oidAseg = oidAseg;
    prelaycmd->u.hidePart.oidPart = oidPart;
}
