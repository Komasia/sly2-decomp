/* func_001E05A0: appends a RELAYCK_ApplySm command to the relay (oidSm, oidUnk5, oidState, fUnk7); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E05A0(RELAY *prelay, int oidSm, int oidUnk5, int oidState, int fAsync, int fUnk7)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ApplySm, fAsync);
    prelaycmd->u.applySm.oidSm = oidSm;
    prelaycmd->u.applySm.oidUnk5 = oidUnk5;
    prelaycmd->u.applySm.oidState = oidState;
    prelaycmd->u.applySm.fUnk7 = fUnk7;
    if (fUnk7) prelaycmd->fAsync = 1;
}
