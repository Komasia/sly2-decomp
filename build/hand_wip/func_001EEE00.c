struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int pad[3]; struct VTE *vt; int x10; struct O *pPrev; struct O *pNext; };
struct STK { int x0; int c; void *a[1]; };
int func_001EF6F0(void);
void func_002333B4(void *p, int b, int cb);
struct O *func_001EF138(void *pv, void *pmem);
struct O *func_001EEE00(struct STK *ps, void *pv)
{
    struct O *pPrev;
    void *pmem;
    struct O *po;
    if (ps->c == 0) pPrev = 0; else pPrev = ps->a[ps->c - 1]; pmem = ps->a[ps->c++]; func_002333B4(pmem, 0, func_001EF6F0()); po = func_001EF138(pv, pmem); po->x10 = ps->x0; po->pPrev = pPrev;
    if (pPrev) pPrev->pNext = po;
    po->vt[7].pfn((char *)po + po->vt[7].d);
    return po;
}
