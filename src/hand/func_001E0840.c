/* func_001E0840: appends a RELAYCK_SetTunnel command to the relay (oidTunnel, oidActor); asynchronous (the script does not wait for it). Called from the Splice binding func_00107900. */
#include "relay.h"

void func_001E0840(RELAY *prelay, int oidTunnel, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_SetTunnel, 1);
    prelaycmd->u.setTunnel.oidTunnel = oidTunnel;
    prelaycmd->u.setTunnel.oidActor = oidActor;
}
