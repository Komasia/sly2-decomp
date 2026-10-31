/* func_00111780 (0x111780): factory (CLS::pfnNew) of class 56 (STEPGUARD), derived from class 51 (STEP): allocate a
 * zeroed 0x1010-byte object and run the class constructor (func_00256360). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00256360(BASIC *pbasic);   /* class 56 (STEPGUARD) constructor */

BASIC *func_00111780(void)
{
    return func_00256360((BASIC *)__builtin_new(0x1010));
}
