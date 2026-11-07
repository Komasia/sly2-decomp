/* func_001E19B0: appends a RELAYCK_ClearHintBox command to the relay (idHint); asynchronous (the script does not wait for it). Called from the Splice binding func_0010A2F8. */
#include "relay.h"

void func_001E19B0(RELAY *prelay, int idHint)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ClearHintBox, 1);
    prelaycmd->u.clearHintBox.idHint = idHint;
}
