/* func_001E1910: appends a RELAYCK_Unk51 command to the relay (oidActor); the script waits for it to complete. Called from the Splice binding func_0010A130. */
#include "relay.h"

void func_001E1910(RELAY *prelay, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk51, 0);
    prelaycmd->u.unk51.oidActor = oidActor;
}
