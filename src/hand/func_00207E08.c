long MaskOfList__FPv(int a);
void *PkindeOfMask__FP5GUARDUl(void *p, long id);
void func_00207D98(void *p, int a, int b, float c, float d, float e, float f);
void ResolveKinde__FP5KINDEP5GUARD(void *pe, void *p);
void func_00207E08(void *p, int a, int b, float c, float d, float e, float f)
{
    void *pe = PkindeOfMask__FP5GUARDUl(p, MaskOfList__FPv(a));
    func_00207D98(p, a, b, c, d, e, f);
    ResolveKinde__FP5KINDEP5GUARD(pe, p);
}
