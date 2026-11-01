/* func_0014FD50: whether this policy is the camera's active one (the top of its policy stack). */
#include "cm.h"

int func_0014FD50(CPLCY *pcplcy)
{
    return D_002DDF40.acpr[0].pcplcy == pcplcy;
}
