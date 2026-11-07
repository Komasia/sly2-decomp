struct S { char pad[0x164]; void *x; char y[4]; };
void OnSoAdd__FP2SO(struct S *p);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *a, struct S *p, int b, int c, void *d);
// name: SafeHouse port (OnCarryAdd)
void OnCarryAdd__FP2LO(struct S *p)
{
    OnSoAdd__FP2SO(p);
    if (p->x) ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(p->x, p, -1, 0, p->y);
}
