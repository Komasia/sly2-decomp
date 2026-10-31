/* func_001E18E0: appends a RELAYCK_Unk50 command to the relay (oidActor); the script waits for it to complete. Called from the Splice binding func_0010A0A8. */
#include "relay.h"

void func_001E18E0(RELAY *prelay, int oidActor)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk50, 0);
    prelaycmd->u.unk50.oidActor = oidActor;
}
