/* func_001E1458: appends a RELAYCK_TweenAimObj command to the relay (oidObj); fAsync from the caller. Called from the Splice binding func_00109540. */
#include "relay.h"

void func_001E1458(RELAY *prelay, int oidObj, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_TweenAimObj, fAsync);
    prelaycmd->u.tweenAimObj.oidObj = oidObj;
}
