struct CMX { char pad[0x300]; int n; float a; float b; };
void func_0014D8D8(struct CMX *p, float a, float b)
{
    int m = 2;
    p->b = b;
    p->a = a;
    if (m < p->n) m = p->n;
    p->n = m;
}
