/* func_001E0820: appends a RELAYCK_Unk17 command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00107888. */
#include "relay.h"

void func_001E0820(RELAY *prelay)
{
    PcmdNew__FP4SCPTii(prelay, RELAYCK_Unk17, 1);
}
