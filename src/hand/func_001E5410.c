/* RUN::ReleaseSmaWatch: stops watching the state machine of the script's ApplySm command: removes the script as its
 * listener, releases it (vt slot 2) and clears the wait. */
#include "relay.h"
struct SMA { char pad[0xC]; VTENT *vt; };
void RemoveLoListener__FP2LOi(struct SMA *psma, JSG *pjsg);
// name: SafeHouse port (RUN::ReleaseSmaWatch)
void ReleaseSmaWatch__3RUN(JSG *pjsg)
{
    if (pjsg->psmaCur) {
        RemoveLoListener__FP2LOi(pjsg->psmaCur, pjsg);
        { struct SMA *psma = pjsg->psmaCur; ((void (*)(void *))psma->vt[2].pfn)(VT_THIS(psma, &psma->vt[2])); }
        pjsg->psmaCur = 0;
        pjsg->fSmaReached = 0;
    }
}
