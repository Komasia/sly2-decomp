/* func_001E1178: appends a RELAYCK_Sound command to the relay (idSnd, oidA, nUnk6, nUnk7, gUnk8, gUnk9, gUnk10); asynchronous (the script does not wait for it). */
#include "relay.h"

void func_001E1178(RELAY *prelay, int idSnd, int oidA, int nUnk6, int nUnk7, float gUnk8, float gUnk9, float gUnk10)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Sound, 1);
    prelaycmd->u.sound.idSnd = idSnd;
    prelaycmd->u.sound.oidA = oidA;
    prelaycmd->u.sound.nUnk6 = nUnk6;
    prelaycmd->u.sound.nUnk7 = nUnk7;
    prelaycmd->u.sound.gUnk8 = gUnk8;
    prelaycmd->u.sound.gUnk9 = gUnk9;
    prelaycmd->u.sound.gUnk10 = gUnk10;
}
