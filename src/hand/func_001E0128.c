/* func_001E0128: the context object of the script that is waiting in a Signal command of this relay (0 when no
 * script waits on a signal). */
#include "relay.h"

LO *func_001E0128(RELAY *prelay)
{
    JSG *pjsg = prelay->pjsgSignal;

    if (pjsg == NULL || pjsg->prelaycmdCur->relayck != RELAYCK_Signal) {
        return 0;
    }
    return pjsg->ploContext;
}
