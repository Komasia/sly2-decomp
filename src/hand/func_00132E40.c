/* class: LO (SafeHouse spliceglue.cpp: the sidebag option setters 0x132BC8..0x132E40, here called by the loader's
 * method 0x100760): the object's sidebag option iopt ensured to a null object reference (0x1294C0 with 0). */
#include "splice.h"
#include "so.h"

struct LO;
CRef *func_001294C0(CRef *pref, BASIC *pbasic);   /* CRef of an object */
CRef *RefEnsureOption(CRef *pref, struct LO *plo, int iopt, CRef *prefValue) asm("RefEnsureOption__FP5BASICiP4CRef");
void Decref(CRef *pref) asm("Decref__4CRef");

void func_00132E40(struct LO *plo, int iopt)
{
    CRef ref;
    CRef refT;

    func_001294C0(&ref, 0);
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
