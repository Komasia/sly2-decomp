/* func_001E0C98: appends a RELAYCK_Unk26 command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00108398. */
#include "relay.h"

void func_001E0C98(RELAY *prelay)
{
    PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk26, 1);
}
