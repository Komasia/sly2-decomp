/* func_00110AB0 (0x110AB0): factory (CLS::pfnNew) of class 1 (SW), derived from class 0 (BASIC): allocate a zeroed
 * 0x4790-byte object and run the class constructor (func_0020D9D0). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_0020D9D0(BASIC *pbasic);   /* class 1 (SW) constructor */

BASIC *func_00110AB0(void)
{
    return func_0020D9D0((BASIC *)__builtin_new(0x4790));
}
