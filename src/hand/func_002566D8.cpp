#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char x10[4]; };
struct DESC { int cb; int align; DESC(int c, int a) { cb = c; align = a; } };
struct MARK { int a[4]; };
extern "C" {
void *__10STACKSCOPE(MARK *);
void _$_10STACKSCOPE(MARK *, int);
void *PvAllocStackImpl(DESC *) asm("PvAllocStackImpl__Fi");
int S32Read(void *) asm("S32Read__18CBinaryInputStream");
void Reserve(void *, int) asm("Reserve__9CDynArrayi");
void *s1_memset(void *, int, int) asm("memset");
}

extern "C" void func_002566D8(O *p, void *pv)
{
    ((void (*)(void *))p->vt[2].pfn)(VT_THIS(p, &p->vt[2]));
    MARK m;
    __10STACKSCOPE(&m);
    DESC d(4, 0x10);
    void *buf = PvAllocStackImpl(&d);
    int n = S32Read(pv);
    Reserve(p->x10, n);
    if (n > 0) do {
        s1_memset(buf, 0, 4);
        ((void (*)(void *, void *, void *))p->vt[4].pfn)(VT_THIS(p, &p->vt[4]), buf, pv);
        ((void (*)(void *, void *))p->vt[5].pfn)(VT_THIS(p, &p->vt[5]), buf);
    } while (--n);
    _$_10STACKSCOPE(&m, 2);
}
