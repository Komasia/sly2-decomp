/* class: LO (SafeHouse spliceglue.cpp: the sidebag option setters 0x132BC8..0x132E40, here called by the loader's
 * method 0x100558): the object's sidebag option iopt ensured to an LM (a limit pair) value (its CRef built by
 * 0x129398, tag 0x1D). */
#include "splice.h"

struct LO;
typedef struct LM { float gMin; float gMax; } LM;
CRef *func_00129398(CRef *pref, const LM *plm);   /* CRef of an LM */
CRef *RefEnsureOption(CRef *pref, struct LO *plo, int iopt, CRef *prefValue) asm("RefEnsureOption__FP5BASICiP4CRef");
void Decref(CRef *pref) asm("Decref__4CRef");

void func_00132D28(struct LO *plo, int iopt, const LM *plm)
{
    CRef ref;
    CRef refT;

    func_00129398(&ref, plm);
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
