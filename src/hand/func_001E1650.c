/* func_001E1650: appends a RELAYCK_Unk46 command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00109A40. */
#include "relay.h"

void func_001E1650(RELAY *prelay)
{
    func_001E01F8(prelay, RELAYCK_Unk46, 1);
}
