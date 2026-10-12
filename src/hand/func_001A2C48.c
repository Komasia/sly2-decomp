struct E { int a; int b; };
extern unsigned int D_002E1E58;
extern struct E D_002BFBD0[];
void func_001A2C48(int *pa, int *pb)
{
    struct E *pe;
    if (D_002E1E58 >= 7) D_002E1E58 = 0;
    pe = &D_002BFBD0[D_002E1E58];
    if (pa) *pa = pe->a;
    if (pb) *pb = pe->b;
}
