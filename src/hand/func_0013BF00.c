/* PostLoadBooty__FP2LO: PostLoad (virtual slot 14) of class 103, derived from class 48 (SO): the SO PostLoad (func_001F36A8), then the
 * class's own part. */
#include "so.h"

void func_001F36A8(SO *p);
void SetBootyState__FP2LOi(void *, int);

// name: SafeHouse port (PostLoadBooty)
void PostLoadBooty__FP2LO(SO *p)
{
    func_001F36A8(p);
    SetBootyState__FP2LOi(p, 0);
}
