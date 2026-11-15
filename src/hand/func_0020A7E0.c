/* FTargetrecExpired (0x20A7E0): whether a pursuit target record's timer is older than D_002C3DB4. */
#include "clock.h"
extern float D_002C3DB4;
struct TARGETREC { float t0; float tTimer; };
// name: SafeHouse port (aipursuit.h FTargetrecExpired, orig 0x20A7E0)
int FTargetrecExpired__FP9TARGETREC(struct TARGETREC *ptargetrec) { return g_clock.t - ptargetrec->tTimer > D_002C3DB4; }
