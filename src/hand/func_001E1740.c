/* func_001E1740: appends a RELAYCK_Unk4A command to the relay (gUnk4, nUnk5, nUnk6, oidActor); the script waits for it to complete. */
#include "relay.h"

void func_001E1740(RELAY *prelay, int nUnk5, int nUnk6, int oidActor, float gUnk4)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk4A, 0);
    prelaycmd->u.unk4A.gUnk4 = gUnk4;
    prelaycmd->u.unk4A.nUnk5 = nUnk5;
    prelaycmd->u.unk4A.nUnk6 = nUnk6;
    prelaycmd->u.unk4A.oidActor = oidActor;
}
