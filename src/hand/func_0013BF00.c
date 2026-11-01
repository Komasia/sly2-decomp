/* func_0013BF00: PostLoad (virtual slot 14) of class 103, derived from class 48 (SO): the SO PostLoad (func_001F36A8), then the
 * class's own part. */
#include "so.h"

void func_001F36A8(SO *p);
void func_0013C560(void *, int);

void func_0013BF00(SO *p)
{
    func_001F36A8(p);
    func_0013C560(p, 0);
}
