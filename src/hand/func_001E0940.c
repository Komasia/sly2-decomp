/* func_001E0940: appends a RELAYCK_HeroState command to the relay (nUnk4, nState, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E0940(RELAY *prelay, int nUnk4, int nState, int fAsync, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_HeroState, fAsync);
    prelaycmd->u.heroState.nUnk4 = nUnk4;
    prelaycmd->u.heroState.nState = nState;
    prelaycmd->u.heroState.oidActor = oidActor;
}
