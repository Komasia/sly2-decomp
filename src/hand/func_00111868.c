/* func_00111868 (0x111868): factory (CLS::pfnNew) of class 60, derived from class 56 (STEPGUARD): allocate a zeroed
 * 0x10A0-byte object, run the class 56 (STEPGUARD) constructor (func_00256360) and install its own vtable
 * (D_002D4820). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00256360(BASIC *pbasic);   /* class 56 (STEPGUARD) constructor */
extern VTE D_002D4820[];   /* class 60 vtable */

BASIC *func_00111868(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x10A0);

    func_00256360(pbasic);
    pbasic->pvt = D_002D4820;
    return pbasic;
}
