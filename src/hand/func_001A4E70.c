/* func_001A4E70 (0x1A4E70): whether the front end's action queue has an action left to run. */
#include "h5_frontq.h"

int func_001A4E70(struct ACTIONQ *pq)
{
    return pq->iact < (int)pq->cact;
}
