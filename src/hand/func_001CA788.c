/* func_001CA788: Init (virtual slot 6) of class 7 / class 6, derived from class 6: the XFM Init, then the class's
 * own part. */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
void func_001A6CA8(void *, int);

void func_001CA788(XFM *p)
{
    InitXfm__FP3XFM(p);
    func_001A6CA8(p, 0);
}
