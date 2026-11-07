long MaskOfList__FPv(int a);
void *PkindeOfMask__FP5GUARDUl(void *p, long id);
void SetGuardKind3__FP5GUARDiiiii(void *p, int a, int b, int c, int d, int e);
void ResolveKinde__FP5KINDEP5GUARD(void *pe, void *p);
void func_00207CF8(void *p, int a, int b, int c, int d, int e)
{
    void *pe = PkindeOfMask__FP5GUARDUl(p, MaskOfList__FPv(a));
    SetGuardKind3__FP5GUARDiiiii(p, a, b, c, d, e);
    ResolveKinde__FP5KINDEP5GUARD(pe, p);
}
