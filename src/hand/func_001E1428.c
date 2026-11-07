/* func_001E1428: appends a RELAYCK_TweenPosObj command to the relay (oidObj); fAsync from the caller. Called from the Splice binding func_00109498. */
#include "relay.h"

void func_001E1428(RELAY *prelay, int oidObj, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_TweenPosObj, fAsync);
    prelaycmd->u.tweenPosObj.oidObj = oidObj;
}
