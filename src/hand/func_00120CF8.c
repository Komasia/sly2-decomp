/* BIF set-cdr!: through RefOpSetCadr. */
#include "splice.h"
void RefOpSetCadr__FiP4CRefP6CFrame4BIFK(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
CRef *RefOpSetCdr__FiP4CRefP6CFrame(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    RefOpSetCadr__FiP4CRefP6CFrame4BIFK(ret, pbasic, cref, aref, 0x24);
    return ret;
}
