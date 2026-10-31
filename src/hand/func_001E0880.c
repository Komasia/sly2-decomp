/* func_001E0880: appends a RELAYCK_SetFocus command to the relay (oidFocus, oidActor); asynchronous (the script does not wait for it). Called from the Splice binding func_001079A8. */
#include "relay.h"

void func_001E0880(RELAY *prelay, int oidFocus, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetFocus, 1);
    prelaycmd->u.setFocus.oidFocus = oidFocus;
    prelaycmd->u.setFocus.oidActor = oidActor;
}
