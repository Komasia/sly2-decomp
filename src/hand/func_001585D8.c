typedef struct MSG { int cb; int nKind; } MSG;
void *PvAllocStackClearImpl__Fi(MSG *pmsg);
static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocStackClearImpl__Fi(pmsg); }
struct S { int cdzMax; char pad[0x4C]; int a; int b; int c; int d; void *pv; };
struct S *InitDzgRows__FP3DZGi(struct S *p, int c);
// name: SafeHouse port (InitDzg)
struct S *InitDzg__FP3DZGiiii(struct S *p, int a, int b, int c, int d)
{
    MSG msg;
    InitDzgRows__FP3DZGi(p, a * 2);
    p->a = a;
    p->b = b;
    p->c = c;
    p->d = d;
    msg.nKind = 0x10;
    msg.cb = 0x60 * p->cdzMax;
    p->pv = PvAllocStackClearImpl__Fi(&msg);
    return p;
}
