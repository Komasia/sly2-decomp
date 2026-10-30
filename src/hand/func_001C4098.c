/* func_001C4098 (0x1C4098): does the PO have a controller (func_001C4080 != -1)? */
#include "po.h"

int func_001C4080(PO *ppo);

int func_001C4098(PO *ppo)
{
    return func_001C4080(ppo) != -1;
}
