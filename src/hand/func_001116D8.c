/* func_001116D8 (0x1116D8): factory (CLS::pfnNew) of class 53 (JT), derived from class 52: allocate a zeroed
 * 0x2060-byte object and run the class constructor (func_002563E8). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_002563E8(BASIC *pbasic);   /* class 53 (JT) constructor */

BASIC *func_001116D8(void)
{
    return func_002563E8((BASIC *)__builtin_new(0x2060));
}
