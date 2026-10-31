/* func_00112C90 (0x112C90): factory (CLS::pfnNew) of class 129, derived from class 126: allocate a zeroed
 * 0x220-byte object, run the class 126 constructor (func_00212158) and install its own vtable (D_002DAD90). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00212158(BASIC *pbasic);   /* class 126 constructor */
extern VTE D_002DAD90[];   /* class 129 vtable */

BASIC *func_00112C90(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x220);

    func_00212158(pbasic);
    pbasic->pvt = D_002DAD90;
    return pbasic;
}
