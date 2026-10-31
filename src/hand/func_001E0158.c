/* func_001E0158: sets the context object of the script that is waiting in a Signal command of this relay. */
#include "relay.h"

void func_001E0158(RELAY *prelay, LO *ploContext)
{
    JSG *pjsg = prelay->pjsgSignal;

    if (pjsg != NULL && pjsg->prelaycmdCur->relayck == RELAYCK_Signal) {
        pjsg->ploContext = ploContext;
    }
}
