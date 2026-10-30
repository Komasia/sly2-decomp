/* func_00113A30 (0x113A30): virtual slot 5 of class 2 (LO): return its class descriptor. */
#include "cls.h"

extern CLS D_002BAB10;   /* class 2 (LO): super class 0 (BASIC), ids [2, 134), 0x50 bytes */

CLS *func_00113A30(void)
{
    return &D_002BAB10;
}
