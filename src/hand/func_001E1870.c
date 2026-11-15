/* func_001E1870: appends a RELAYCK_Unk4F command to the relay (nUnk5, nUnk7, nUnk6, nUnk8, oidActor); its fAsync argument decides whether the script waits for it. */
#include "relay.h"

void func_001E1870(RELAY *prelay, int nUnk5, int nUnk7, int nUnk6, int nUnk8, int oidActor, int fAsync)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk4F, fAsync);
    prelaycmd->u.unk4F.nUnk5 = nUnk5;
    prelaycmd->u.unk4F.nUnk7 = nUnk7;
    prelaycmd->u.unk4F.nUnk6 = nUnk6;
    prelaycmd->u.unk4F.nUnk8 = nUnk8;
    prelaycmd->u.unk4F.oidActor = oidActor;
}
