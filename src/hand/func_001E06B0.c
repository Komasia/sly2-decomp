/* func_001E06B0: appends a RELAYCK_SetTaskState command to the relay (oidTask, nState); asynchronous (the script does not wait for it). Called from the Splice binding func_001074C8. */
#include "relay.h"

void func_001E06B0(RELAY *prelay, int oidTask, int nState)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_SetTaskState, 1);
    prelaycmd->u.setTaskState.oidTask = oidTask;
    prelaycmd->u.setTaskState.nState = nState;
}
