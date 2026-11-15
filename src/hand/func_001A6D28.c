#include "vtbl.h"
struct ALO {
    char pad[0x28];
    unsigned long b0 : 52;
    long n52 : 4;
    unsigned int b56 : 4;
    unsigned int f60 : 1;
};
struct SW { struct ALO *palo; };
struct O {
    char pad[0xC];
    VTENT *vt;
    struct O *pNext;
    struct SW *psw;
    char pad2[0x15];
    unsigned char b2D;
};
extern char g_sw[];
void QueueLoRoot__FP2SWP2LO(void *, void *);
void func_001A6D28(struct O *p, int b)
{
    struct O *q;
    if (p->psw->palo->f60)
        QueueLoRoot__FP2SWP2LO(g_sw, p->psw);
    {
        VTENT *e = &p->vt[46];
        ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), b);
    }
    for (q = p->pNext; q; q = q->pNext)
        q->b2D |= b;
}
