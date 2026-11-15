/* func_001E1670: appends a RELAYCK_Unk47 command to the relay (oidActor, nUnk5, nUnk6); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E1670(RELAY *prelay, int oidActor, int nUnk5, int nUnk6)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk47, 1);
    prelaycmd->u.unk47.oidActor = oidActor;
    prelaycmd->u.unk47.nUnk5 = nUnk5;
    prelaycmd->u.unk47.nUnk6 = nUnk6;
}
