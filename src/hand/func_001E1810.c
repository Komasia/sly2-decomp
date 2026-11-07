/* func_001E1810: appends a RELAYCK_StopMusic command to the relay (idMusic); asynchronous (the script does not wait for it). Called from the Splice binding func_00109EA8. */
#include "relay.h"

void func_001E1810(RELAY *prelay, int idMusic)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StopMusic, 1);
    prelaycmd->u.stopMusic.idMusic = idMusic;
}
