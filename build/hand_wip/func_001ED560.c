struct S { int n; };
extern struct S **D_003DD018;
void func_001ED560(struct S *p)
{
    int i = p->n % 0x3FFD;
    while (D_003DD018[i]) i = (i + 1) % 0x3FFD;
    D_003DD018[i] = p;
}
