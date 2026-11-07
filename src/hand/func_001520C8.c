/* func_001520C8: OnRemove (virtual slot 11) of class 68, derived from class 51 (STEP): the SO OnRemove, then the
 * class's own part. */
#include "so.h"

void OnSoRemove__FP2SO(SO *p);
void PlayDancerAseg__FP2LOT0i(void *, int, int);

void func_001520C8(SO *p)
{
    OnSoRemove__FP2SO(p);
    PlayDancerAseg__FP2LOT0i(p, 0, 0);
}
