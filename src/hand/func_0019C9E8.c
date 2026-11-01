/* func_0019C9E8: OnAdd (virtual slot 10) of class 40, derived from class 3 (XFM): the LO OnAdd, then it joins its
 * class list (D_003E1420). */
#include "so.h"

void OnLoAdd__FP2LO(LO *p);
void AppendDlEntry__FP2DLPv(void *, void *);
extern char D_003E1420[];

void func_0019C9E8(LO *p)
{
    OnLoAdd__FP2LO(p);
    AppendDlEntry__FP2DLPv(D_003E1420, p);
}
