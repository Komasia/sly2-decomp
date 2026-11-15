#include "cid.h"
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int n);
// name: SafeHouse port (JtlDescFromLo)
void *JtlDescFromLo__FP2LO(char *p)
{
    if (!p) return 0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_HIDE)) return p + 0x150;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_CRAWLHOOK)) return p + 0x130;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_WALL)) return p + 0xE0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_LEDGE)) return p + 0x190;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_USE)) return p + 0xE0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x13)) return p + 0x100;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_PIPE)) return p + 0x190;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, 0xD)) return p + 0x190;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p, CID_SPIRE)) return p + 0xE0;
    return 0;
}
