struct T { char pad[0xE8]; int ne8; char pad2[8]; int nf4; };
int CposNavPath__FP9NAVREGIONG9VU_VECTORT1iP7VECTOR4(void *p, int a, int b, int c, int d);
void func_001E6180(struct T *pt);
// name: SafeHouse port (FNavPathCrv)
int FNavPathCrv__FP9NAVREGIONiiP3CRV(char *p, int a, int b, struct T *pt)
{
    int n = CposNavPath__FP9NAVREGIONG9VU_VECTORT1iP7VECTOR4(p + 0xE0, a, b, 0x10, pt->nf4);
    if (n < 2) return 0;
    pt->ne8 = n;
    func_001E6180(pt);
    return 1;
}
