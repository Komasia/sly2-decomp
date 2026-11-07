/* func_001E0910: appends a RELAYCK_Unk1B command to the relay (oidActor); the script waits for it to complete. Called from the Splice binding func_00107B18. */
#include "relay.h"

void func_001E0910(RELAY *prelay, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk1B, 0);
    prelaycmd->u.unk1B.oidActor = oidActor;
}
