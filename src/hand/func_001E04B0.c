/* func_001E04B0: appends a RELAYCK_Signal command to the relay (idSignal); asynchronous (the script does not wait for it). Called from the Splice binding func_00106F90. */
#include "relay.h"

void func_001E04B0(RELAY *prelay, int idSignal)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Signal, 1);
    prelaycmd->u.signal.idSignal = idSignal;
}
