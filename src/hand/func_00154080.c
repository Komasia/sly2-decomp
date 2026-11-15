#include "cid.h"
#include "clock.h"
#include "vtbl.h"
extern char g_game[];
struct E { int id; int n; float t; float tC; };
struct O { int a[3]; VTENT *vt; void *p10; };
struct ARGS { struct E *pe; int *pn; int *pnNew; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *q);
// name: SafeHouse port (SetDetentryState)
void SetDetentryState__FP8DETECTORP8DETENTRYi(struct O *o, struct E *pe, int nNew)
{
    struct ARGS args;
    VTENT *e;
    if (!pe || nNew == pe->n)
        return;
    if (pe->n == 0)
        pe->tC = g_clock.t;
    args.pe = pe;
    args.pn = &pe->n;
    args.pnNew = &nNew;
    e = &o->vt[3];
    ((void (*)())e->pfn)(VT_THIS(o, e), 0x1C, 0, 3, &args, 0);
    pe->n = nNew;
    pe->t = g_clock.t;
    if (nNew == 1) {
        void *q = o->p10;
        if (q && FIsBasicDerivedFrom__FP5BASIC3CID(q, CID_STEP))
            BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x13, q);
    }
}
