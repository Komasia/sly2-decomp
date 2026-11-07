struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[3]; };
struct X { char pad[0xC]; struct VT *pvt; };
void RetractSma__FP3SMA(struct X *);
struct X *func_001F03A8(void *, int, int, int, int);
// name: SafeHouse port (ReplaceSmaHandleMask)
void ReplaceSmaHandleMask__FP2SMi3OIDiUiPP3SMA(void *pv, int a, int b, int c, int d, struct X **ppx)
{
    if (*ppx) {
        RetractSma__FP3SMA(*ppx);
        (*ppx)->pvt->a[2].pfn((char *)*ppx + (*ppx)->pvt->a[2].d);
        *ppx = 0;
    }
    if (pv) {
        struct X *px = func_001F03A8(pv, a, b, c, d);
        *ppx = px;
        px->pvt->a[1].pfn((char *)px + px->pvt->a[1].d);
    }
}
