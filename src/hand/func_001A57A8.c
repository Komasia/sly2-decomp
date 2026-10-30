/* func_001A57A8 (0x1A57A8): unlink the LO from its parent's child list. func_001A5448 returns the list and the
 * parent's "first removed child" link; if that link points at this LO it moves on to the next sibling. */
#include "so.h"

void func_001A5448(SO *psoParent, DL **ppdl, LO ***ppploFirst);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);

void func_001A57A8(LO *plo)
{
    DL *pdl;
    LO **pploFirst;

    func_001A5448(plo->psoParent, &pdl, &pploFirst);
    if (*pploFirst == plo)
        *pploFirst = (LO *)plo->dleChild.next;
    RemoveDlEntry__FP2DLPv(pdl, plo);
}
