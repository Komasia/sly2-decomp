/* func_001E15B0: appends a RELAYCK_Unk43 command to the relay (nUnk4, oidActor); the script waits for it to complete. Called from the Splice binding func_00109868. */
#include "relay.h"

void func_001E15B0(RELAY *prelay, int nUnk4, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk43, 0);
    prelaycmd->u.unk43.nUnk4 = nUnk4;
    prelaycmd->u.unk43.oidActor = oidActor;
}
