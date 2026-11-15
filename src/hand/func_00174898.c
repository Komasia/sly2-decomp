#include "cid.h"
/* func_00174898: the guard an object belongs to: its parent's object when that is a guard (CID_STEPGUARD), or for a
 * bomb the guard owning the bomb's +0x200 object; else 0. */
struct LO;
struct LINK { struct LO *plo; };
struct LO { char pad[0x14]; struct LINK *plink; char pad2[0x1E8]; struct LO *plo200; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *plo, int n);
struct LO *func_00174898(struct LO *plo) {
    if (!plo) return 0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo->plink->plo, CID_STEPGUARD)) return plo->plink->plo;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_BOMB) && FIsBasicDerivedFrom__FP5BASIC3CID(plo->plo200->plink->plo, CID_STEPGUARD)) return plo->plo200->plink->plo;
    return 0;
}
