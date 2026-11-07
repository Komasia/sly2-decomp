/* OnRemoveNoiseListener__FP2LO: OnRemove (virtual slot 11) of class 47, derived from class 3 (XFM): the LO OnRemove, then it
 * leaves its class list (D_003E1468). */
#include "so.h"

void OnLoRemove__FP2LO(LO *p);
void RemoveDlEntry__FP2DLPv(void *, void *);
void func_00156DE0(void *, int);
extern char D_003E1468[];

// name: SafeHouse port (OnRemoveNoiseListener)
void OnRemoveNoiseListener__FP2LO(LO *p)
{
    OnLoRemove__FP2LO(p);
    func_00156DE0(p, 1);
    RemoveDlEntry__FP2DLPv(D_003E1468, p);
}
