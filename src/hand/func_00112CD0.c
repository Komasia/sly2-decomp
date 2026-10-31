/* func_00112CD0 (0x112CD0): factory (CLS::pfnNew) of class 130, derived from class 126: allocate a zeroed
 * 0x130-byte object and run the class constructor (func_00211C58). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00211C58(BASIC *pbasic);   /* class 130 constructor */

BASIC *func_00112CD0(void)
{
    return func_00211C58((BASIC *)__builtin_new(0x130));
}
