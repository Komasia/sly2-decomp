/* func_001E10C8: appends a RELAYCK_Explode command to the relay (oidA, oidB, oidC, dtDelay); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E10C8(RELAY *prelay, int oidA, int oidB, int oidC, float dtDelay)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Explode, 1);
    prelaycmd->u.explode.oidA = oidA;
    prelaycmd->u.explode.oidB = oidB;
    prelaycmd->u.explode.oidC = oidC;
    prelaycmd->u.explode.dtDelay = dtDelay;
}
