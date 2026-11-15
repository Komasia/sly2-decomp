/* func_001E16C0: appends a RELAYCK_Unk48 command to the relay (oidActor, nUnk5, nUnk6); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E16C0(RELAY *prelay, int oidActor, int nUnk5, int nUnk6)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk48, 1);
    prelaycmd->u.unk48.oidActor = oidActor;
    prelaycmd->u.unk48.nUnk5 = nUnk5;
    prelaycmd->u.unk48.nUnk6 = nUnk6;
}
