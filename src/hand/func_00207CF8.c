long func_00207B10(int a);
void *func_00209C18(void *p, long id);
void func_00207C48(void *p, int a, int b, int c, int d, int e);
void ResolveKinde__FP5KINDEP5GUARD(void *pe, void *p);
void func_00207CF8(void *p, int a, int b, int c, int d, int e)
{
    void *pe = func_00209C18(p, func_00207B10(a));
    func_00207C48(p, a, b, c, d, e);
    ResolveKinde__FP5KINDEP5GUARD(pe, p);
}
