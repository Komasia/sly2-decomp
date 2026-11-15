#include "vtbl.h"
struct VT { VTENT a[6]; };
struct Q { char pad[0xC]; VT *pvt; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x28 - 0x10]; Q *pq; };
extern "C" void func_00133508(P *, int, int);
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; ((void (*)(void *))p->pvt->a[1].pfn)(VT_THIS(p, &p->pvt->a[1])); }
    ~Lock() { ((void (*)(void *))p->pvt->a[2].pfn)(VT_THIS(p, &p->pvt->a[2])); }
};
extern "C" void func_001F0FD8(P *p, int a, int b)
{
    Lock l(p);
    Q *q = p->pq;
    if (q) ((void (*)(void *, int, int))q->pvt->a[5].pfn)(VT_THIS(q, &q->pvt->a[5]), a, b);
    func_00133508(p, a, b);
}
