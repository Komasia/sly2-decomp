/* func_001A5B80 (0x1A5B80): LO virtual slot 12 (SO overrides it and calls this as super): set up the LO's
 * LOROOT. A child shares its parent's root (after func_001A53E0 when it is its own clone source and fNew is 0);
 * a top-level LO gets a fresh root when fNew is set. */
#include "so.h"

void func_001A53A0(LO *plo);
void func_001A53E0(LO *plo);

void func_001A5B80(LO *plo, LO *ploSrc, int fNew)
{
    if (plo->psoParent != NULL) {
        if (ploSrc == plo && fNew == 0)
            func_001A53E0(plo);
        plo->ploroot = plo->psoParent->lo.ploroot;
        return;
    }
    if (fNew != 0) {
        plo->ploroot = NULL;
        func_001A53A0(plo);
    }
}
