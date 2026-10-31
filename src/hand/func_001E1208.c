/* func_001E1208: appends a RELAYCK_StopSound command to the relay (idSnd); asynchronous (the script does not wait for it). Called from the Splice binding func_00109088. */
#include "relay.h"

void func_001E1208(RELAY *prelay, int idSnd)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_StopSound, 1);
    prelaycmd->u.stopSound.idSnd = idSnd;
}
