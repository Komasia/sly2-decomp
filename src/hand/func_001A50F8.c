/* class: the front end's action queue (SafeHouse frontend.cpp 0x1A4E08; it calls this at its initialisation): queues
 * the memory card check action (kind 5). */
#include "h5_frontq.h"
void func_001A4FB0(void *pqueue, int actk);

void func_001A50F8(void *pqueue)
{
    func_001A4FB0(pqueue, ACTK_CARD);
}
