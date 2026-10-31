/* func_001E1408: appends a RELAYCK_EndJtMode command to the relay (no arguments); fAsync from the caller. Called from the Splice binding func_00109418. */
#include "relay.h"

void func_001E1408(RELAY *prelay, int fAsync)
{
    func_001E01F8(prelay, RELAYCK_EndJtMode, fAsync);
}
