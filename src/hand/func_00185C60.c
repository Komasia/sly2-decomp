/* func_00185C60: OnRemove (virtual slot 11) of class 9, derived from class 8: the LO OnRemove, then it leaves its
 * class list (D_003E142C). */
#include "so.h"

void OnLoRemove__FP2LO(LO *p);
void RemoveDlEntry__FP2DLPv(void *, void *);
extern char D_003E142C[];

void func_00185C60(LO *p)
{
    OnLoRemove__FP2LO(p);
    RemoveDlEntry__FP2DLPv(D_003E142C, p);
}
