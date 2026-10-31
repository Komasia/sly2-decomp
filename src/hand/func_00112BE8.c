/* func_00112BE8 (0x112BE8): factory (CLS::pfnNew) of class 126, derived from class 2 (LO): allocate a zeroed
 * 0x110-byte object and run the class constructor (func_00212158). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00212158(BASIC *pbasic);   /* class 126 constructor */

BASIC *func_00112BE8(void)
{
    return func_00212158((BASIC *)__builtin_new(0x110));
}
