struct D { int a; char *b; int c; char *d; };
struct H { short a; short b; };
void func_0016D698(int n, struct D *pd, struct H **pph)
{
    struct H *ph = (*pph)++;
    ph->a = n;
    ph->b = ((pd->d - pd->b) >> 4) + 0x23;
}
