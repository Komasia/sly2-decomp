/* func_001E0450: appends a RELAYCK_SetCtlState command to the relay (oidObj); asynchronous (the script does not wait for it). Called from the Splice binding func_00106E80. */
#include "relay.h"

void func_001E0450(RELAY *prelay, int oidObj)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetCtlState, 1);
    prelaycmd->u.setCtlState.oidObj = oidObj;
}
