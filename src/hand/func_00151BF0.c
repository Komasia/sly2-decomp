/* Activate__6CPPAIRP2LOPv: CPTWOSHOT virtual slot 1: the CPLCY one (Activate__5CPLCYP2LOPv, same arguments), then the two
 * objects to frame. */
#include "cm.h"

void Activate__5CPLCYP2LOPv(CPTWOSHOT *pcptwoshot, LO *ploHero, LO *ploOwner);

// name: SafeHouse port (CPPAIR::Activate)
void Activate__6CPPAIRP2LOPv(CPTWOSHOT *pcptwoshot, LO *ploHero, LO *ploOwner)
{
    Activate__5CPLCYP2LOPv(pcptwoshot, ploHero, ploOwner);
    pcptwoshot->ploHero = ploHero;
    pcptwoshot->ploOwner = ploOwner;
}
