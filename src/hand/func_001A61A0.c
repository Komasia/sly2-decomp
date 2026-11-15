/* FLoActive (0x1A61A0): an LO is active when it is in the world (bit 60 of +0x28) and its root (+0x14) is in the
 * active roots list D_003DD4BC. SafeHouse activate.h. */
#include "dl.h"
typedef unsigned long ulong;
extern struct DL g_dlActiveRoots __asm__("D_003DD4BC");
int FFindDlEntry__FP2DLPv(struct DL *pdl, void *pv);
struct S { char pad[0x14]; void *ploroot; char pad2[0x10]; ulong fl; };
// name: SafeHouse port (activate.h FLoActive, orig 0x1A61A0)
int FLoActive__FP2LO(struct S *plo)
{
    int fActive = 0;
    if ((int)(plo->fl >> 60) & 1) fActive = FFindDlEntry__FP2DLPv(&g_dlActiveRoots, plo->ploroot) != 0;
    return fActive;
}
