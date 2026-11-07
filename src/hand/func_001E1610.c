/* func_001E1610: appends a RELAYCK_Line command to the relay (idLine, fWait); fAsync from the caller. Called from the Splice binding func_00109988. */
#include "relay.h"

void func_001E1610(RELAY *prelay, int idLine, int fWait, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Line, fAsync);
    prelaycmd->u.line.idLine = idLine;
    prelaycmd->u.line.fWait = fWait;
}
