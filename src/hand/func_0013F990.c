/* The object's sink value (LO +0x28 bits 48..51, SafeHouse lo.h: 0x13F990) set, and for an SO its children's too. */
#include "cid.h"
struct LO { char pad[0x24]; struct LO *ploSibling; unsigned long grfLo : 48; unsigned long nSink : 4; unsigned long grfHi : 12; char pad2[0x64 - 0x30]; struct LO *ploFirstChild; };   /* LO +0x28 bits 48..51 the sink's value (SafeHouse lo.h); SO +0x64 its children */
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *, int);
void func_0013F990(struct LO *plo, int n) {
    struct LO *ploChild;
    plo->nSink = n;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_SO)) {
        for (ploChild = plo->ploFirstChild; ploChild; ploChild = ploChild->ploSibling) func_0013F990(ploChild, n);
    }
}
