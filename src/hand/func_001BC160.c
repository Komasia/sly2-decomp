/* func_001BC160: OnAdd (virtual slot 10) of class 14, derived from class 10: the LO OnAdd, then it joins its class
 * list (D_003E1A4C). */
#include "so.h"

void OnLoAdd__FP2LO(LO *p);
void AppendDlEntry__FP2DLPv(void *, void *);
extern char D_003E1A4C[];

void func_001BC160(LO *p)
{
    OnLoAdd__FP2LO(p);
    AppendDlEntry__FP2DLPv(D_003E1A4C, p);
}
