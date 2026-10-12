struct VTE { short d; short p; void (*pfn)(void *, int); };
struct VT { struct VTE a[22]; };
struct Q { char pad[0xC]; struct VT *pvt; };
struct P { char pad[0x494]; struct Q *pq; };
#ifdef __cplusplus
extern "C" {
#endif
void func_00205D10(struct P *, int);
#define VF(q, n) (q)->pvt->a[21].pfn((char *)(q) + (q)->pvt->a[21].d, n)
void func_001F1F38(struct P *p, int f)
{
    func_00205D10(p, f);
    if (f) { if (p->pq) VF(p->pq, 0); }
    else if (p->pq) VF(p->pq, 1);
}
#ifdef __cplusplus
}
#endif
