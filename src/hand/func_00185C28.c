/* func_00185C28: OnAdd (virtual slot 10) of class 9, derived from class 8: the LO OnAdd, then it joins its class
 * list (D_003E142C). */
#include "so.h"

void OnLoAdd__FP2LO(LO *p);
void AppendDlEntry__FP2DLPv(void *, void *);
extern char D_003E142C[];

void func_00185C28(LO *p)
{
    OnLoAdd__FP2LO(p);
    AppendDlEntry__FP2DLPv(D_003E142C, p);
}
