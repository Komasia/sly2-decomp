struct CMX { char pad[0x300]; int n; float a; float b; };
// name: SafeHouse port (SetCmCut)
void SetCmCut__FP2CMff(struct CMX *p, float a, float b)
{
    int m = 2;
    p->b = b;
    p->a = a;
    if (m < p->n) m = p->n;
    p->n = m;
}
