/* SetTargetrecTimer (0x20A9A8): restarts a pursuit target record's timer with a value (1 seen, 2 lost but near,
 * 3 an action, 4 a shot, 5 hit). */
#include "clock.h"
struct TARGETREC { float t0; float tTimer; int nTimer; };
// name: SafeHouse port (SetTargetrecTimer)
void SetTargetrecTimer__FP9TARGETRECi(struct TARGETREC *ptargetrec, int nTimer) { ptargetrec->tTimer = g_clock.t; ptargetrec->nTimer = nTimer; }
