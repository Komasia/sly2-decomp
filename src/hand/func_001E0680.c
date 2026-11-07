/* func_001E0680: appends a RELAYCK_SetClockRate command to the relay (rate); asynchronous (the script does not wait for it). Called from the Splice binding func_00107440. */
#include "relay.h"

void func_001E0680(RELAY *prelay, float rate)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_SetClockRate, 1);
    prelaycmd->u.setClockRate.rate = rate;
}
