#include "cid.h"
#define OID_GUARDACTION_DEFAULT 0x2CC
/* the guard's action oids (option 233) and their objects */
struct GUARD { char pad[0xEB8]; int aoidAction[8]; int coidAction; int aploAction[8]; int cploAction; };
int PloNew__F3CIDP2SW3OIDi(int cid, struct GUARD *ploParent, int oid, int n);
/* appends an action and its oid */
static __inline__ void Push(struct GUARD *pguard, int oid, int plo)
{
    pguard->aploAction[pguard->cploAction++] = plo;
    pguard->aoidAction[pguard->coidAction++] = oid;
}
/* func_0020A9C0 (0x20A9C0): the guard's first action object; a guard with none gets a default one (cid 0x78 oid
 * 716). */
int func_0020A9C0(struct GUARD *pguard)
{
    int plo;
    if (pguard->coidAction == 0) {
        plo = PloNew__F3CIDP2SW3OIDi(CID_GUARDACTION, pguard, OID_GUARDACTION_DEFAULT, -1);
        Push(pguard, OID_GUARDACTION_DEFAULT, plo);
    } else {
        plo = pguard->aploAction[0];
    }
    return plo;
}
