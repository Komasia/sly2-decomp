/* func_001A5078 (0x1A5078): queues a world transition action (kind 2) to a world file key, at a warp oid with the
 * request's flags, unless the key is no file (its +0x4 equals its +0x3C). */
#include "h5_frontq.h"
struct FK { int x0; int x4; char pad[0x34]; int x3c; };
struct ACTION *func_001A4FB0(void *pq, int actk);
static inline int FWorld(struct FK *pfk) { if (!pfk) return 0; return pfk->x4 != pfk->x3c; }
void func_001A5078(void *pq, struct FK *pfk, int oid, int grf)
{
    if (FWorld(pfk)) {
        struct ACTION *pact = func_001A4FB0(pq, ACTK_WORLD);
        pact->pbWorld = pfk;
        pact->oidWorld = oid;
        pact->grfWorld = grf;
    }
}
