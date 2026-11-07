/* func_001C4098 (0x1C4098): does the PO have a controller (NPoEnabled__FP2LO != -1)? */
#include "po.h"

int NPoEnabled__FP2LO(PO *ppo);

int func_001C4098(PO *ppo)
{
    return NPoEnabled__FP2LO(ppo) != -1;
}
