/* func_001E06F0: appends a RELAYCK_HandsOff command to the relay (fHandsOff, grfHandsOff); asynchronous (the script does not wait for it). Called from the Splice binding func_00107570. */
#include "relay.h"

void func_001E06F0(RELAY *prelay, int fHandsOff, int grfHandsOff)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_HandsOff, 1);
    prelaycmd->u.handsOff.fHandsOff = fHandsOff;
    prelaycmd->u.handsOff.grfHandsOff = grfHandsOff;
}
