/* func_001E1388: appends a RELAYCK_Unk3A command to the relay (nUnk4); asynchronous (the script does not wait for it). Called from the Splice binding func_001092D0. */
#include "relay.h"

void func_001E1388(RELAY *prelay, int nUnk4)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk3A, 1);
    prelaycmd->u.unk3A.nUnk4 = nUnk4;
}
