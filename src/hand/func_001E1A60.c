/* func_001E1A60: appends a RELAYCK_Unk57 command to the relay (oidActor); asynchronous (the script does not wait for it). Called from the Splice binding func_0010A4E0. */
#include "relay.h"

void func_001E1A60(RELAY *prelay, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk57, 1);
    prelaycmd->u.unk57.oidActor = oidActor;
}
