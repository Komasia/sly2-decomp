/* RUN::OnSmaState: the script's state-machine notification: the base handler (empty func_00133590), then, for a
 * state-reached message (10) from the state machine the script's ApplySm command runs (JSG psmaCur) about the state
 * that command waits for, marks the wait done (fSmaReached). */
#include "relay.h"
typedef struct SMAMSG { void *psma; int unk_0x4; OID oidState; } SMAMSG;   /* fields by use */
#define SMAMSGK_Reached 10
void func_00133590(JSG *pjsg, int smamsgk, SMAMSG *pmsg);
// name: SafeHouse port (RUN::OnSmaState)
void OnSmaState__3RUNiP8SMAMSG10(JSG *pjsg, int smamsgk, SMAMSG *pmsg)
{
    func_00133590(pjsg, smamsgk, pmsg);
    if (smamsgk == SMAMSGK_Reached && pmsg->psma == pjsg->psmaCur && pmsg->oidState == pjsg->prelaycmdCur->u.applySm.oidState)
        pjsg->fSmaReached = 1;
}
