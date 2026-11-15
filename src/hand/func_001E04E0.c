/* func_001E04E0: appends a RELAYCK_PlayAseg command to the relay (oidAseg, oidRoot, grfapl); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E04E0(RELAY *prelay, int oidAseg, int oidRoot, int fAsync, int grfapl)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_PlayAseg, fAsync);
    prelaycmd->u.playAseg.oidAseg = oidAseg;
    prelaycmd->u.playAseg.oidRoot = oidRoot;
    prelaycmd->u.playAseg.grfapl = grfapl;
}
