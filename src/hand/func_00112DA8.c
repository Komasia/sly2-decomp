/* func_00112DA8 (0x112DA8): factory (CLS::pfnNew) of class 135, derived from class 0 (BASIC): allocate a zeroed
 * 0x630-byte object and run the class constructor (__2CM). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *__2CM(BASIC *pbasic);   /* class 135 constructor */

BASIC *func_00112DA8(void)
{
    return __2CM((BASIC *)__builtin_new(0x630));
}
