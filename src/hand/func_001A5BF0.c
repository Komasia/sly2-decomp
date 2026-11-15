/* PaloOrParent (0x1A5BF0): the object itself when it is an ALO (CID_SO, SafeHouse ALO), else its parent. SafeHouse so.cpp. */
#include "cid.h"
struct S { char pad[0x10]; struct S *x10; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct S *p, int n);
// name: SafeHouse port (PaloOrParent)
struct S *PaloOrParent__FPv(struct S *plo) { if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_SO)) return plo; return plo->x10; }
