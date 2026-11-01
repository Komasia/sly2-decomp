/* func_00156D20: OnAdd (virtual slot 10) of class 47, derived from class 3 (XFM): the LO OnAdd, then it joins its
 * class list (D_003E1468). */
#include "so.h"

void OnLoAdd__FP2LO(LO *p);
void AppendDlEntry__FP2DLPv(void *, void *);
extern char D_003E1468[];

void func_00156D20(LO *p)
{
    OnLoAdd__FP2LO(p);
    AppendDlEntry__FP2DLPv(D_003E1468, p);
}
