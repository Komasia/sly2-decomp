/* func_001E0C78: appends a RELAYCK_Unk25 command to the relay (no arguments); asynchronous (the script does not wait for it). Called from the Splice binding func_00108320. */
#include "relay.h"

void func_001E0C78(RELAY *prelay)
{
    func_001E01F8(prelay, RELAYCK_Unk25, 1);
}
