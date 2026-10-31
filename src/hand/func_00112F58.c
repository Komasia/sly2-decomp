/* func_00112F58 (0x112F58): factory (CLS::pfnNew) of class 145, derived from class 0 (BASIC): allocate a zeroed
 * 0x70-byte object and run the class constructor (func_0020C058). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_0020C058(BASIC *pbasic);   /* class 145 constructor */

BASIC *func_00112F58(void)
{
    return func_0020C058((BASIC *)__builtin_new(0x70));
}
