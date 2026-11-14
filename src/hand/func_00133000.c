/* class: the splice event of an object (SafeHouse update.cpp / aijob.cpp: orig 0x1331F8 / 0x132ED8 / 0x133000): the
 * form evaluated in the object's frame (RefEval), the result assigned to the caller's CRef if it wants it. */
#include "splice.h"

CRef *RefEval(CRef *pref, CPair *ppair, CFrame *pframe) asm("RefEval__FP5CPairP6CFrame");
CRef *__as__4CRefRC4CRef(CRef *pref, const CRef *prefSrc);   /* CRef::operator= */
void Decref(CRef *pref) asm("Decref__4CRef");

void func_00133000(void *plo, CPair *ppairForm, CFrame *pframe, CRef *prefResult)
{
    CRef ref;

    RefEval(&ref, ppairForm, pframe);
    if (prefResult != 0) {
        __as__4CRefRC4CRef(prefResult, &ref);
    }
    Decref(&ref);
}
