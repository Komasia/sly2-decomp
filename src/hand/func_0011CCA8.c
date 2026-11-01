/* func_0011CCA8: SLOTHEAP constructor (used by the g++ static initialisers for every CStructTypeFactory<T>::s_slotheap):
 * slot size, slots per block, alignment; no block allocated yet. */
#include "slotheap.h"

SLOTHEAP *func_0011CCA8(SLOTHEAP *pslotheap, int cb, int cslot, int cbAlign)
{
    pslotheap->cb = cb;
    pslotheap->cslot = cslot;
    pslotheap->cbAlign = cbAlign;
    pslotheap->pvFirst = 0;
    return pslotheap;
}
