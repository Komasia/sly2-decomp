/* func_001E03E0: appends a RELAYCK_RaiseAlarm command to the relay (idAlarm, oidRelay); asynchronous (the script does not wait for it). Called from the Splice binding func_00106D50. */
#include "relay.h"

void func_001E03E0(RELAY *prelay, int idAlarm, int oidRelay)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_RaiseAlarm, 1);
    prelaycmd->u.raiseAlarm.idAlarm = idAlarm;
    prelaycmd->u.raiseAlarm.oidRelay = oidRelay;
}
