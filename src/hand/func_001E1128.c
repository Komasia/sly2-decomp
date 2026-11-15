/* func_001E1128: appends a RELAYCK_Eyes command to the relay (oidA, oidB, dtEyes); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E1128(RELAY *prelay, int oidA, int oidB, float dtEyes)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Eyes, 1);
    prelaycmd->u.eyes.oidA = oidA;
    prelaycmd->u.eyes.oidB = oidB;
    prelaycmd->u.eyes.dtEyes = dtEyes;
}
