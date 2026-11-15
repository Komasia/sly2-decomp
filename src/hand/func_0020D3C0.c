#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
/* an object: its vtable; for the water, its contact state (+0x184) and filter (+0x188) */
struct LOV { char pad[0xC]; VTENT *pvt; char pad2[0x184 - 0x10]; int nState; int grfFilter; };
struct WATCHB { struct LOV *pguard; int st; float t; struct LOV *pwater; };
/* the contact message (CTMSG) */
struct CTMSG { struct LOV *ploSender; int pad; struct LOV *ploReceiver; int grfFilter; int nState; int pad2[3]; qword pos; qword vec; char pad3[0x20]; };
extern struct { float t; float dt; } g_clock;
void s1_memset(void *pv, int c, int cb) asm("memset");
qword PosOfLo__FP2LO(struct LOV *plo);
void PaloAcceptContact__FP5CTMSG(struct CTMSG *pctm);
/* SetWatchB (0x20D3C0): the water watcher's state, noting when it changed; state 2 sends the guard the water's
 * contact (its filter and state) at the guard's position and velocity (vt slot 33). */
// name: SafeHouse port (SetWatchB)
void SetWatchB__FP6WATCHBi(struct WATCHB *pwatch, int st)
{
    if (st != pwatch->st) {
        pwatch->st = st;
        pwatch->t = g_clock.t;
        if (st == 2) {
            struct CTMSG ctm;
            s1_memset(&ctm, 0, sizeof(ctm));
            ctm.ploSender = pwatch->pwater;
            ctm.ploReceiver = pwatch->pguard;
            ctm.grfFilter = pwatch->pwater->grfFilter;
            ctm.nState = pwatch->pwater->nState;
            ctm.pos = PosOfLo__FP2LO(pwatch->pguard);
            ctm.vec = ((qword (*)(void *))pwatch->pguard->pvt[33].pfn)(VT_THIS(pwatch->pguard, &pwatch->pguard->pvt[33]));
            PaloAcceptContact__FP5CTMSG(&ctm);
        }
    }
}
