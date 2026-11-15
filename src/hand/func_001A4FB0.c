/* func_001A4FB0 (0x1A4FB0): appends a cleared action of the given kind to the front end's queue and returns it; when
 * the queue is full (16) the dummy action D_002E1E68 is returned instead. */
#include "h5_frontq.h"
extern struct ACTION g_actDummy __asm__("D_002E1E68");
void s1_memset(void *, int, int) asm("memset");
struct ACTION *func_001A4FB0(struct ACTIONQ *pq, int actk)
{
    struct ACTION *pact;
    if (pq->cact >= 16)
        return &g_actDummy;
    pact = &pq->aact[pq->cact++];
    s1_memset(pact, 0, sizeof(struct ACTION));
    pact->actk = actk;
    return pact;
}
