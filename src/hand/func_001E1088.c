/* func_001E1088: appends a RELAYCK_Rumble command to the relay (dtRumble, rumk); fAsync from the caller. Called from the Splice binding func_00108D48. */
#include "relay.h"

void func_001E1088(RELAY *prelay, int rumk, int fAsync, float dtRumble)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Rumble, fAsync);
    prelaycmd->u.rumble.dtRumble = dtRumble;
    prelaycmd->u.rumble.rumk = rumk;
}
