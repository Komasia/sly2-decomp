/* func_001E1510: appends a RELAYCK_TweenTime command to the relay (gUnk4); fAsync from the caller. Called from the Splice binding func_001096A0. */
#include "relay.h"

void func_001E1510(RELAY *prelay, int fAsync, float gUnk4)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_TweenTime, fAsync);
    prelaycmd->u.tweenTime.gUnk4 = gUnk4;
}
