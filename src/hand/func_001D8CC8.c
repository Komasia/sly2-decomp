/* class: progress path: a new KEY (on the stack heap) that is path pkeyA followed by path pkeyB. */
#include "h3_progress.h"
struct MSG { int cb; int nKind; };
void *PvAllocStackImpl__Fi(struct MSG *pmsg);
void CopyAb(void *pvDst, void *pvSrc, int cb) asm("CopyAb__FPvT0Ui");

KEY *func_001D8CC8(KEY *pkeyA, KEY *pkeyB)
{
    struct MSG msg;
    KEY *pkey;
    int csym;
    msg.cb = 8;
    msg.nKind = 0x10;
    pkey = (KEY *)PvAllocStackImpl__Fi(&msg);
    csym = pkeyA->csym + pkeyB->csym;
    pkey->csym = csym;
    msg.cb = csym * 2;
    msg.nKind = 0x10;
    pkey->asym = (unsigned short *)PvAllocStackImpl__Fi(&msg);
    CopyAb(pkey->asym, pkeyA->asym, pkeyA->csym * 2);
    CopyAb(pkey->asym + pkeyA->csym, pkeyB->asym, pkeyB->csym * 2);
    return pkey;
}
