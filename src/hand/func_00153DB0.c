/* func_00153DB0: Update (virtual slot 15) of class 16, derived from class 3 (XFM): the LO Update (func_001A5E28), then the class's
 * own part. */
#include "so.h"

void func_001A5E28(LO *p, float dt);
void func_00153DE0(void *);

void func_00153DB0(LO *p, float dt)
{
    func_001A5E28(p, dt);
    func_00153DE0(p);
}
