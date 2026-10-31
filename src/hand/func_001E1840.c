/* func_001E1840: appends a RELAYCK_WaitTimer command to the relay (dtWait); the script waits for it to complete. Called from the Splice binding func_00109F30. */
#include "relay.h"

void func_001E1840(RELAY *prelay, float dtWait)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_WaitTimer, 0);
    prelaycmd->u.waitTimer.dtWait = dtWait;
}
