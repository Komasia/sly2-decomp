#include "cid.h"
#include "vtbl.h"
struct Y { char pad[0xC]; VTENT *vt; };
struct D { int a; int b; int c; int d; };
int CploFindSwNearest__FP2LO3OIDiiii(void *p, int k, int a, int b, int c, void **ppo);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *o, int n);
struct Y *PsmaFindAloSm__Fi3OID(void *o, int b);
void AddLoListener__FP2LOi(struct Y *y, int x);
void SnapSmaGoal__FP3SMA3OID(struct Y *y, int id);
void SetSmaGoal__FP3SMA3OID(struct Y *y, int id);
void func_0020FFF0(void *p, struct D *pd, int b, int fl, int x, struct Y **ppy)
{
    void *o;
    struct Y *y;
    int id;
    if (ppy)
        *ppy = 0;
    if (CploFindSwNearest__FP2LO3OIDiiii(p, 0x204, pd->a, b, 1, &o) != 1)
        return;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(o, CID_SO))
        return;
    y = PsmaFindAloSm__Fi3OID(o, pd->b);
    if (!y)
        return;
    if (fl & 1)
        id = pd->c;
    else
        id = pd->d;
    if (id == -1)
        return;
    if (x) {
        *ppy = y;
        ((void (*)(void *))y->vt[1].pfn)(VT_THIS(y, &y->vt[1]));
        AddLoListener__FP2LOi(y, x);
    }
    if (fl & 2)
        SnapSmaGoal__FP3SMA3OID(y, id);
    else
        SetSmaGoal__FP3SMA3OID(y, id);
}
