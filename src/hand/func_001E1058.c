/* func_001E1058: appends a RELAYCK_Unk32 command to the relay (nUnk4); fAsync from the caller. Called from the Splice binding func_00108CA0. */
#include "relay.h"

void func_001E1058(RELAY *prelay, int nUnk4, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk32, fAsync);
    prelaycmd->u.unk32.nUnk4 = nUnk4;
}
