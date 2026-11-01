/* func_0014FD50: whether this policy is the camera's active one (the top of its policy stack). */
#include "cm.h"

int func_0014FD50(CPLCY *pcplcy)
{
    return g_cm.acpr[0].pcplcy == pcplcy;
}
