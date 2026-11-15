/* SetWatchA (0x20D108): the fall watcher's state, noting when it changed; state 2 sends the guard the fall contact
 * (filter 0x4000) from itself. */
#include "clock.h"
struct CTMSG { int an[0x18]; };   /* +0x0 the sender, +0x8 the receiver, +0xC the filter, +0x10 the state */
struct WATCHA { int pguard; int st; float t; };
void *s1_memset(void *pv, int c, int cb) asm("memset");
void PaloAcceptContact__FP5CTMSG(struct CTMSG *pctm);
// name: SafeHouse port (SetWatchA)
void SetWatchA__FP6WATCHAi(struct WATCHA *pwatch, int st)
{
    if (pwatch->st == st) return;
    pwatch->st = st;
    pwatch->t = g_clock.t;
    if (st == 2) {
        struct CTMSG ctm;
        s1_memset(&ctm, 0, sizeof ctm);
        ctm.an[3] = 0x4000;
        ctm.an[0] = pwatch->pguard;
        ctm.an[2] = pwatch->pguard;
        ctm.an[4] = 0;
        PaloAcceptContact__FP5CTMSG(&ctm);
    }
}
