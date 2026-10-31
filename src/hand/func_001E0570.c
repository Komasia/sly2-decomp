/* func_001E0570: appends a RELAYCK_SetContext command to the relay (oidContext); asynchronous (the script does not wait for it). Called from the Splice binding func_00107198. */
#include "relay.h"

void func_001E0570(RELAY *prelay, int oidContext)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetContext, 1);
    prelaycmd->u.setContext.oidContext = oidContext;
}
