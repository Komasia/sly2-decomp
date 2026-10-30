/* func_00113A40 (0x113A40): virtual slot 5 of class 3 (ALO): return its class descriptor. */
#include "cls.h"

extern CLS D_002BAB24;   /* class 3 (ALO): super class 2 (LO), ids [3, 48), 0xE0 bytes */

CLS *func_00113A40(void)
{
    return &D_002BAB24;
}
