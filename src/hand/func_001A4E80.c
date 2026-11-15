/* func_001A4E80 (0x1A4E80): runs the front end's next queued action (SafeHouse frontend.cpp): a movie (queued on
 * D_002F66B0, then the transition to the boot world D_002BFCA0), a world transition, a task start, nothing, or the
 * memory card's messages on (then the next action at once). */
#include "h5_frontq.h"
struct MOVIEQ { char pad[0x108]; int f108; };
struct CARDMSG { char pad[0x44]; int fOn; };
#define OID_BOOT_WARP 0x189
#define GRF_TRANSITION_TASK 0x30A
extern struct MOVIEQ g_movieq __asm__("D_002F66B0");
extern struct CARDMSG g_cardmsg __asm__("D_002E6550");
extern char g_sw[], g_game[];
extern char g_pbWorldAfterMovie[] __asm__("D_002BFCA0");
int func_001A4E70(struct ACTIONQ *pq);
void QueueMovie__FPUcPv(struct MOVIEQ *pmovieq, void *pbMovie);
void RequestTransition__FP2SWPUc3OIDT2iT2(void *psw, void *pbWorld, int oid, int oidFrom, int grf, int n);
void RequestTaskStartByOid__FP2SWi3OID(void *pgame, int nTask, int oid);
void func_001ACC38(struct CARDMSG *pcardmsg, int fOn);
void func_001A4E80(struct ACTIONQ *pq)
{
    struct ACTION *pact;
    struct MOVIEQ *pmovieq;
    if (!func_001A4E70(pq))
        return;
    pact = &pq->aact[pq->iact++];
    switch (pact->actk) {
    case ACTK_MOVIE:
    case ACTK_MOVIE_F108:
        pmovieq = &g_movieq;
        QueueMovie__FPUcPv(pmovieq, pact->pbMovie);
        if (pact->actk == ACTK_MOVIE_F108)
            pmovieq->f108 = pact->actk;
        RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, g_pbWorldAfterMovie, OID_BOOT_WARP, -1, 0, -1);
        break;
    case ACTK_WORLD:
        RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, pact->pbWorld, pact->oidWorld, -1, pact->grfWorld, GRF_TRANSITION_TASK);
        break;
    case ACTK_TASK:
        RequestTaskStartByOid__FP2SWi3OID(g_game, pact->nTask, pact->oidTask);
        break;
    case ACTK_NONE:
        break;
    case ACTK_CARD:
        if (!g_cardmsg.fOn)
            func_001ACC38(&g_cardmsg, 1);
        func_001A4E80(pq);
        break;
    }
}
