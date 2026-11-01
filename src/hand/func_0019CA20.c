/* func_0019CA20: OnRemove (virtual slot 11) of class 40, derived from class 3 (XFM): the LO OnRemove, then it
 * leaves its class list (D_003E1420). */
#include "so.h"

void OnLoRemove__FP2LO(LO *p);
void RemoveDlEntry__FP2DLPv(void *, void *);
extern char D_003E1420[];

void func_0019CA20(LO *p)
{
    OnLoRemove__FP2LO(p);
    RemoveDlEntry__FP2DLPv(D_003E1420, p);
}
