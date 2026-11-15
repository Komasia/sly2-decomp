/* func_001E0B40: appends a RELAYCK_Face command to the relay (dtWait, oidFace, oidActor); the script waits for it to complete. */
#include "relay.h"

void func_001E0B40(RELAY *prelay, int oidFace, int oidActor, float dtWait)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_Face, 0);
    prelaycmd->u.face.dtWait = dtWait;
    prelaycmd->u.face.oidFace = oidFace;
    prelaycmd->u.face.oidActor = oidActor;
}
