struct S { char pad[0xE8]; float a, b, c; int f; };
void func_00231100(struct S *p);
void func_0021D3D8(struct S *p)
{
    func_00231100(p);
    p->a = 2000.0f;
    p->b = -800.0f;
    p->c = 800.0f;
    p->f = 1;
}
