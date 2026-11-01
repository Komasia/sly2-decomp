/* func_001DE568: PostLoad (virtual slot 14) of class 85, derived from class 84: the SO PostLoad (func_001F36A8), then the class's
 * own part. */
#include "so.h"

void func_001F36A8(SO *p);
void func_001DE5D8(void *);
void func_001DEDB0(void *);
void func_001DF260(void *, int);

void func_001DE568(SO *p)
{
    func_001F36A8(p);
    func_001DE5D8(p);
    func_001DEDB0(p);
    func_001DF260(p, 0);
}
