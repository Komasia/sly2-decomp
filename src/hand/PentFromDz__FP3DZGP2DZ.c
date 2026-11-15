/* PentFromDz: the response entry (DZENT, 0x60 bytes) of a row (DZ, 40 bytes) of a constraint system: the entry at
 * the row's index. Layouts: include/dzg.h. */
#include "dzg.h"

// name: SafeHouse port (PentFromDz)
DZENT *PentFromDz__FP3DZGP2DZ(DZG *pdzg, DZ *pdz)
{
    return &pdzg->aent[pdz - pdzg->adz];
}
