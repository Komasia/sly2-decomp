/* func_001E1940: appends a RELAYCK_Unk52 command to the relay (dtWait); the script waits for it to complete. Called from the Splice binding func_0010A1B8. */
#include "relay.h"

void func_001E1940(RELAY *prelay, float dtWait)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk52, 0);
    prelaycmd->u.unk52.dtWait = dtWait;
}
