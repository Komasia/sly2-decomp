/* func_001A5020 (0x1A5020): queues a movie action (kind 0) for a movie file key, unless the key is no movie (its +0x4
 * equals its +0x3C: SafeHouse frontend.cpp QueueMovie). */
#include "h5_frontq.h"
struct FK { int x0; int x4; char pad[0x34]; int x3c; };
struct ACTION *func_001A4FB0(void *pq, int actk);
static inline int FMovie(struct FK *pfk) { if (!pfk) return 0; return pfk->x4 != pfk->x3c; }
void func_001A5020(void *pq, struct FK *pfk)
{
    if (FMovie(pfk)) func_001A4FB0(pq, ACTK_MOVIE)->pbMovie = pfk;
}
