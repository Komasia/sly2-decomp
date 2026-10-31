/* func_00111828 (0x111828): factory (CLS::pfnNew) of class 59, derived from class 58: allocate a zeroed 0x1020-byte
 * object, run the class 56 (STEPGUARD) constructor (func_00256360) and install its own vtable (D_002CDE40). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00256360(BASIC *pbasic);   /* class 56 (STEPGUARD) constructor */
extern VTE D_002CDE40[];   /* class 59 vtable */

BASIC *func_00111828(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x1020);

    func_00256360(pbasic);
    pbasic->pvt = D_002CDE40;
    return pbasic;
}
