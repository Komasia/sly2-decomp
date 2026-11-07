/* func_001E02C0: appends a RELAYCK_BlockEnd command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00106B08. */
#include "relay.h"

void func_001E02C0(RELAY *prelay)
{
    PcmdNew__FP4SCPTii(prelay, RELAYCK_BlockEnd, 1);
}
