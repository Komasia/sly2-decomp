/* func_00151BF0: CPTWOSHOT virtual slot 1: the CPLCY one (func_0014FCC8, same arguments), then the two
 * objects to frame. */
#include "cm.h"

void func_0014FCC8(CPTWOSHOT *pcptwoshot, LO *ploHero, LO *ploOwner);

void func_00151BF0(CPTWOSHOT *pcptwoshot, LO *ploHero, LO *ploOwner)
{
    func_0014FCC8(pcptwoshot, ploHero, ploOwner);
    pcptwoshot->ploHero = ploHero;
    pcptwoshot->ploOwner = ploOwner;
}
