struct T { char pad[0xD4]; float a, b; };
struct S { char pad[0xE8]; struct T *t; };
void func_001F3590(struct S *p);
void func_001F68A8(struct S *p, int a);
void func_00228BB0(struct S *p)
{
    func_001F3590(p);
    func_001F68A8(p, 1);
    { struct T *t = p->t;
    t->b = 1.0f;
    t->a = 1.0f; }
}
