/* func_001E03A0: appends a RELAYCK_WaitAlarm command to the relay (idAlarm, fForget); the script waits for it to complete. Called from the Splice binding func_00106CA8. */
#include "relay.h"

void func_001E03A0(RELAY *prelay, int idAlarm, int fForget)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_WaitAlarm, 0);
    prelaycmd->u.waitAlarm.idAlarm = idAlarm;
    prelaycmd->u.waitAlarm.fForget = fForget;
}
