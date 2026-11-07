/* func_00134770: LoadFromBrx (virtual slot 13) of class 55, derived from class 52: the STEP LoadFromBrx (LoadPoFromBrx__FP2POP18CBinaryInputStream), then the
 * class's own part. */
#include "step.h"

void LoadPoFromBrx__FP2POP18CBinaryInputStream(STEP *p, struct CBinaryInputStream *pbis);
void BindLoParts__FP3ALOiPv(void *, int, void *);
extern char D_002BC390[];

void func_00134770(STEP *p, struct CBinaryInputStream *pbis)
{
    LoadPoFromBrx__FP2POP18CBinaryInputStream(p, pbis);
    BindLoParts__FP3ALOiPv(p, 0x76, D_002BC390);
}
