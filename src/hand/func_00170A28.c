/* func_00170A28: PostLoad (virtual slot 14) of class 113, derived from class 2 (LO): the LO PostLoad, then the
 * class's own part. */
#include "so.h"

void PostLoLoad__FP2LO(LO *p);
void PostLoadCmdlist__FP7CMDLIST(void *);

void func_00170A28(LO *p)
{
    PostLoLoad__FP2LO(p);
    PostLoadCmdlist__FP7CMDLIST(p);
}
