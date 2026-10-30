struct VT { short d; short pad; void *pfn; };
struct O { char pad[0xC]; VT *vt; char x10[4]; };
struct DESC { int cb; int align; DESC(int c, int a) { cb = c; align = a; } };
struct MARK { int a[4]; };
extern "C" {
void *func_001AE478(MARK *);
void func_001AE4A0(MARK *, int);
void *PvAllocSlot(DESC *) asm("PvAllocSlot__FP8ALLOCREQ");
int func_00117DB8(void *);
void Reserve(void *, int) asm("Reserve__9CDynArrayi");
void *func_002333B4(void *, int, int);
}

extern "C" void func_002566D8(O *p, void *pv)
{
    ((void (*)(void *))p->vt[2].pfn)((char *)p + p->vt[2].d);
    MARK m;
    func_001AE478(&m);
    DESC d(4, 0x10);
    void *buf = PvAllocSlot(&d);
    int n = func_00117DB8(pv);
    Reserve(p->x10, n);
    if (n > 0) do {
        func_002333B4(buf, 0, 4);
        ((void (*)(void *, void *, void *))p->vt[4].pfn)((char *)p + p->vt[4].d, buf, pv);
        ((void (*)(void *, void *))p->vt[5].pfn)((char *)p + p->vt[5].d, buf);
    } while (--n);
    func_001AE4A0(&m, 2);
}
