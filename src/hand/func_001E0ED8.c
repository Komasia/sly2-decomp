/* func_001E0ED8: appends a RELAYCK_AddObject command to the relay (oidObj, dtFade); fAsync from the caller. Called from the Splice binding func_00108890. */
#include "relay.h"

void func_001E0ED8(RELAY *prelay, int oidObj, int fAsync, float dtFade)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_AddObject, fAsync);
    prelaycmd->u.addObject.oidObj = oidObj;
    prelaycmd->u.addObject.dtFade = dtFade;
}
