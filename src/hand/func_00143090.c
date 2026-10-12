struct S8 { float a, b; };
struct X { char pad[0x1120]; struct S8 a, b, c; };
void func_00143090(struct X *p, struct S8 *a, struct S8 *b, struct S8 *c)
{
    p->a = *a;
    p->b = *b;
    p->c = *c;
}
