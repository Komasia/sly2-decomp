/* func_00111700 (0x111700): factory (CLS::pfnNew) of class 54 (MURRAY), derived from class 52: allocate a zeroed
 * 0x1B00-byte object and run the class constructor (func_00256440). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00256440(BASIC *pbasic);   /* class 54 (MURRAY) constructor */

BASIC *func_00111700(void)
{
    return func_00256440((BASIC *)__builtin_new(0x1B00));
}
