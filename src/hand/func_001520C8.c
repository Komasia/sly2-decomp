/* func_001520C8: OnRemove (virtual slot 11) of class 68, derived from class 51 (STEP): the SO OnRemove, then the
 * class's own part. */
#include "so.h"

void OnSoRemove__FP2SO(SO *p);
void func_001524A0(void *, int, int);

void func_001520C8(SO *p)
{
    OnSoRemove__FP2SO(p);
    func_001524A0(p, 0, 0);
}
