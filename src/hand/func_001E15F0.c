/* func_001E15F0: appends a RELAYCK_StopLine command to the relay (no arguments); the script waits for it to complete. Called from the Splice binding func_00109910. */
#include "relay.h"

void func_001E15F0(RELAY *prelay)
{
    func_001E01F8(prelay, RELAYCK_StopLine, 0);
}
