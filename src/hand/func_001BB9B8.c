struct MSG { int cb; int nKind; };
struct I { int a, b; };
struct E { int id; int n; int c; struct I *a; };
struct S { char pad[0x15C]; int i; int c; struct E *ae; };
void *PvAllocSlot__FP8ALLOCREQ(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSlot__FP8ALLOCREQ(pmsg); }
void func_001BB9B8(struct S *p)
{
    struct E *pe;
    struct MSG msg;
    p->i = -1;
    pe = &p->ae[-1];
    pe->id = -1;
    pe->n = 1;
    if (!pe->a) pe->a = PvAllocMsg(&msg, 0x200, 0x10);
}
