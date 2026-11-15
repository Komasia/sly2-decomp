/* func_001DFFE0: clears the relay's script (Splice method 0x106A08): stops it, drops all commands, and starts over with
 * the opening BlockBegin (no label: -1) and the closing BlockEnd still to append - as BeginScptLoad does. */
#include "relay.h"
void StopScptImpl__FP2LO(RELAY *prelay);
void func_001E0290(RELAY *prelay, int oidLabel);   /* append a BlockBegin command */
void func_001DFFE0(RELAY *prelay) {
    StopScptImpl__FP2LO(prelay);
    prelay->crelaycmd = 0;
    func_001E0290(prelay, -1);
    prelay->fAppendEnd = 1;
}
