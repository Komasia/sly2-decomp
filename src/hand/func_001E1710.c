/* func_001E1710: appends a RELAYCK_Unk49 command to the relay (nUnk4); asynchronous (the script does not wait for it). Called from the Splice binding func_00109C28. */
#include "relay.h"

void func_001E1710(RELAY *prelay, int nUnk4)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk49, 1);
    prelaycmd->u.unk49.nUnk4 = nUnk4;
}
