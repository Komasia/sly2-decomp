/* func_0016F148: Init (virtual slot 6) of class 57, a STEPGUARD subclass: initialise the guard, then set the flag at
 * +0xE78. (Earlier named RenderGomerSelf: the code is the class's Init slot - it calls InitStepguard - while Sly 1's
 * RenderGomerSelf only forwards to RenderStepguardSelf. The class itself is not identified.) */
#include "common.h"

struct STEPGUARD;
void InitStepguard(STEPGUARD *pstepguard);

extern "C" void func_0016F148(STEPGUARD *pstepguard)
{
    InitStepguard(pstepguard);
    STRUCT_OFFSET(pstepguard, 0xE78, int) = 1;
}
