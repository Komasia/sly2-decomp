/* PloNew: a new object of class cid (its class's pfnNew) under paloParent with its oid: its splice frame (0x1FFA40 by
 * iframe), in the world's lists by oid and by class, initialised (vt slot 7), added (slot 11) when in the world,
 * activated (slot 23) when active, and appended to the loader's list. SafeHouse port (lo.h: PloNew's psw argument
 * is the parent, orig +0x10). */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *pvt; void *paloParent; int pnode; int oid; int x1C; int x20; int x24; int x28; signed char x2C; char x2D; long k:4; long :8; unsigned int fInWorld:1; };   /* LO +0x28 bit 60 (SafeHouse lo.h) */
struct CLS { int x0; int x4; int x8; int xC; struct LO *(*pfnNew)(void); };
struct SW { char pad[0x39E4]; struct LO **pploLoaded; };   /* the loader's list of new objects */
extern struct CLS D_002BAAE8[];   /* the class descriptors by cid (cls.h) */
extern struct SW g_sw;
void *func_001FFA40(struct SW *pswWorld, int n, struct LO *plo);
void func_00256EE0(struct LO *plo, void *pv);
void *func_0015E380(struct SW *pswWorld, int oid);
void *func_0015E3A8(struct SW *pswWorld, int cid);
void func_0011A070(void *pdl, struct LO *plo);
int FLoActive__FP2LO(struct LO *plo);
#define VCALL(p, n) ((void (*)(void *))(p)->pvt[n].pfn)(VT_THIS((p), &(p)->pvt[n]))
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, void *paloParent, int oid, int iframe)
{
    struct SW *pswWorld; struct LO *plo = (D_002BAAE8 + cid)->pfnNew();
    plo->paloParent = paloParent;
    plo->oid = oid;
    pswWorld = &g_sw;
    func_00256EE0(plo, func_001FFA40(pswWorld, iframe, plo));
    func_0011A070(func_0015E380(pswWorld, oid), plo);
    func_0011A070(func_0015E3A8(pswWorld, cid), plo);
    VCALL(plo, 7);
    if (plo->fInWorld)
        VCALL(plo, 11);
    if (FLoActive__FP2LO(plo))
        VCALL(plo, 23);
    if (pswWorld->pploLoaded)
        *pswWorld->pploLoaded++ = plo;
    return plo;
}
