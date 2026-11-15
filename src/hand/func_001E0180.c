/* PrunFind: the first script (JSG) of the relay, other than pjsgSkip, whose block opens with a BlockBegin labelled
 * oidLabel (StopBlock / WaitBlocks look blocks up by label); 0 if none. */
#include "relay.h"
// name: SafeHouse port (PrunFind)
JSG *PrunFind__FP4SCPTiP3RUN(RELAY *prelay, OID oidLabel, JSG *pjsgSkip)
{
    int unused[4];
    JSG *pjsg;
    for (pjsg = prelay->dlJsg.head; pjsg; pjsg = pjsg->dleRelay.next) {
        if (pjsg != pjsgSkip && pjsg->prelaycmdFirst->u.blockBegin.oidLabel == oidLabel) return pjsg;
    }
    return 0;
}
