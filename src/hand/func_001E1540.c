/* func_001E1540: appends a RELAYCK_Unk41 command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00109748. */
#include "relay.h"

void func_001E1540(RELAY *prelay)
{
    func_001E01F8(prelay, RELAYCK_Unk41, 1);
}
