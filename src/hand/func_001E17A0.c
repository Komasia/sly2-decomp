/* func_001E17A0: appends a RELAYCK_PlayAsegDefault command to the relay (oidOther, oidActor); asynchronous (the script does not wait for it). Called from the Splice binding func_00109D78. */
#include "relay.h"

void func_001E17A0(RELAY *prelay, int oidOther, int oidActor)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_PlayAsegDefault, 1);
    prelaycmd->u.playAsegDefault.oidOther = oidOther;
    prelaycmd->u.playAsegDefault.oidActor = oidActor;
}
