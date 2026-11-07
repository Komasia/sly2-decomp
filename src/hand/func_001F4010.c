typedef int qword __attribute__((mode(TI)));
struct M4 { qword a[4]; };
struct T { struct M4 m; char pad[0xA4 - 0x40]; int nA4; };
struct VTE { short d; short p; int (*pfn)(void *); };
struct VT { struct VTE a[19]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x54 - 0x10]; struct T *pt; };
struct G { char pad[0x3D58]; int n; };
extern struct G g_sw;
struct M4 MulMatrix4__FP7MATRIX4T0Pv(void *, struct T *);
void RemeasureAloPairs__FP3ALO(struct P *);
// name: SafeHouse port (SetAloMatrix)
void SetAloMatrix__FP3ALOP7MATRIX4(struct P *p, void *pv)
{
    struct T *pt = p->pt;
    pt->m = MulMatrix4__FP7MATRIX4T0Pv(pv, pt);
    { int n = ++g_sw.n; p->pt->nA4 = n; }
    p->pvt->a[18].pfn((char *)p + p->pvt->a[18].d);
    RemeasureAloPairs__FP3ALO(p);
}
