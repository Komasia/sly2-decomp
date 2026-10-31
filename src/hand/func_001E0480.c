/* func_001E0480: appends a RELAYCK_SetActor command to the relay (oidActor); asynchronous (the script does not wait for it). Called from the Splice binding func_00106F08. */
#include "relay.h"

void func_001E0480(RELAY *prelay, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetActor, 1);
    prelaycmd->u.setActor.oidActor = oidActor;
}
