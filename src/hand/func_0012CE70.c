/* class: an ASEGA's list record (RetractAsega frees each record of the ASEGA's +0x38 list with it, after its object's
 * vtable slot 44): the record's slot returned to its slot heap D_003E1254. */
#include "slotheap.h"

extern SLOTHEAP D_003E1254;
void func_0011CD98(SLOTHEAP *pslotheap, void *pv);

void func_0012CE70(void *prec)
{
    func_0011CD98(&D_003E1254, prec);
}
