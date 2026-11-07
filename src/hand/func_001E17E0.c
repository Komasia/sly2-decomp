/* func_001E17E0: appends a RELAYCK_StartMusic command to the relay (idMusic); asynchronous (the script does not wait for it). Called from the Splice binding func_00109E20. */
#include "relay.h"

void func_001E17E0(RELAY *prelay, int idMusic)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_StartMusic, 1);
    prelaycmd->u.startMusic.idMusic = idMusic;
}
