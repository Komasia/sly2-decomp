/* func_00134770: LoadFromBrx (virtual slot 13) of class 55, derived from class 52: the STEP LoadFromBrx (func_002039C0), then the
 * class's own part. */
#include "step.h"

void func_002039C0(STEP *p, struct CBinaryInputStream *pbis);
void func_001A64E8(void *, int, void *);
extern char D_002BC390[];

void func_00134770(STEP *p, struct CBinaryInputStream *pbis)
{
    func_002039C0(p, pbis);
    func_001A64E8(p, 0x76, D_002BC390);
}
