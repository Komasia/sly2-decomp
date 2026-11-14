/* class: LO (SafeHouse spliceglue.cpp: the sidebag option setters 0x132BC8..0x132E40, here called by the loader's
 * method 0x1004A0): the object's sidebag option iopt ensured to a CLQ value (its CRef built by 0x129330). */
#include "splice.h"

struct LO;
CRef *func_00129330(CRef *pref, const qword *pclq);   /* CRef of a CLQ */
CRef *RefEnsureOption(CRef *pref, struct LO *plo, int iopt, CRef *prefValue) asm("RefEnsureOption__FP5BASICiP4CRef");
void Decref(CRef *pref) asm("Decref__4CRef");

void func_00132CC8(struct LO *plo, int iopt, const qword *pclq)
{
    CRef ref;
    CRef refT;

    func_00129330(&ref, pclq);
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
