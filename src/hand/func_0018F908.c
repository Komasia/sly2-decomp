int NewBlend__FP3ALOiiP4ELEMiPiT5Pv(void *p, int a, int b, void *q, int c, int d, int e, int *pn);
// name: SafeHouse port (BindSlySwingBlend)
void BindSlySwingBlend__FP3SLYPvPi(void *p, void *q, int *pn)
{
    int n;
    NewBlend__FP3ALOiiP4ELEMiPiT5Pv(p, 0xC, 3, q, 0, 0, 0, &n);
    if (pn) *pn = n;
}
