/* func_00111A28 (0x111A28): factory (CLS::pfnNew) of class 67, derived from class 56 (STEPGUARD): allocate a zeroed
 * 0x1010-byte object, run the class 56 (STEPGUARD) constructor (func_00256360) and install its own vtable
 * (D_002C8940). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00256360(BASIC *pbasic);   /* class 56 (STEPGUARD) constructor */
extern VTE D_002C8940[];   /* class 67 vtable */

BASIC *func_00111A28(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x1010);

    func_00256360(pbasic);
    pbasic->pvt = D_002C8940;
    return pbasic;
}
