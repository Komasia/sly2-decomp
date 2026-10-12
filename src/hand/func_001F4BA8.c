#include "common.h"
struct T { char pad[0x70]; ulong fl; };
struct S { char pad[0xEC]; struct T *pt; };
struct DL;
extern struct DL D_003E11B8;
void func_0011A2E8(struct DL *, void *);
void func_001F4BA8(struct S *p)
{
    struct T *pt = p->pt;
    if (!pt) return;
    if (!(pt->fl & 1)) return;
    pt->fl &= ~1;
    func_0011A2E8(&D_003E11B8, p->pt);
}
