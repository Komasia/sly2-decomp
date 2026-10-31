/* func_001E0F18: appends a RELAYCK_RemoveObject command to the relay (oidObj, dtFade); fAsync from the caller. Called from the Splice binding func_00108948. */
#include "relay.h"

void func_001E0F18(RELAY *prelay, int oidObj, int fAsync, float dtFade)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_RemoveObject, fAsync);
    prelaycmd->u.removeObject.oidObj = oidObj;
    prelaycmd->u.removeObject.dtFade = dtFade;
}
