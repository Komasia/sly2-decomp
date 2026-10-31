/* func_00112C50 (0x112C50): factory (CLS::pfnNew) of class 128, derived from class 126: allocate a zeroed
 * 0x110-byte object, run the class 126 constructor (func_00212158) and install its own vtable (D_002DAA50). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00212158(BASIC *pbasic);   /* class 126 constructor */
extern VTE D_002DAA50[];   /* class 128 vtable */

BASIC *func_00112C50(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x110);

    func_00212158(pbasic);
    pbasic->pvt = D_002DAA50;
    return pbasic;
}
