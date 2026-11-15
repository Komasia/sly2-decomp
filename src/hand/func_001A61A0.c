#include "dl.h"
typedef unsigned long ulong;
extern struct DL D_003DD4BC;
int FFindDlEntry__FP2DLPv(struct DL *pdl, void *pv);
struct S { char pad[0x14]; void *x14; char pad2[0x10]; ulong fl; };
// name: SafeHouse port (activate.h FLoActive, orig 0x1A61A0)
int FLoActive__FP2LO(struct S *p)
{
    int r = 0;
    if ((int)(p->fl >> 60) & 1) r = FFindDlEntry__FP2DLPv(&D_003DD4BC, p->x14) != 0;
    return r;
}
