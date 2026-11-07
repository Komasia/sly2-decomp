/* func_001E1970: appends a RELAYCK_HintBox command to the relay (idHint, dtHint); fAsync from the caller. Called from the Splice binding func_0010A240. */
#include "relay.h"

void func_001E1970(RELAY *prelay, int idHint, int fAsync, float dtHint)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_HintBox, fAsync);
    prelaycmd->u.hintBox.idHint = idHint;
    prelaycmd->u.hintBox.dtHint = dtHint;
}
