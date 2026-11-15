/* FFindEntryKey (SafeHouse savedata.cpp, orig 0x1D7DA0): walk a path down the progress trie. Each path symbol is
 * looked for among the current node's children (sibling chain); an indexed node takes the next path element as its
 * index. Found (the path used up at a node): the node and index in *pfound, 1. */
#include "h3_progress.h"

// name: SafeHouse port (FFindEntryKey)
int FFindEntryKey__FP4TRIEPP4PENTPi(LAYOUT *playout, KEY *pkey, PENTFOUND *pfound)
{
    PENT *aent = playout->aent;
    PENT *pent;
    int isym;
    if (aent->iChild == 0)
        return 0;
    pent = &aent[aent->iChild];
    pfound->i = 0;
    isym = 0;
    for (;;) {
        if (pent->ch == pkey->asym[isym]) {
            isym++;
            if (isym == pkey->csym) {
                pfound->pent = pent;
                return 1;
            }
            if (pent->fIndexed) {
                pfound->pent = pent;
                pfound->i = pkey->asym[isym++];
                return isym == pkey->csym;
            }
            if (pent->kind != PROGK_Node)
                return 0;
            if (!pent->iChild)
                return 0;
            pent = &playout->aent[pent->iChild];
        } else {
            if (!pent->iSibling)
                return 0;
            pent = &playout->aent[pent->iSibling];
        }
    }
}
