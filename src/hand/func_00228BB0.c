struct T { char pad[0xD4]; float a, b; };
struct S { char pad[0xE8]; struct T *t; };
void RestAloSost__FP3ALO(struct S *p);
void SetAloSensors__FP3ALOi(struct S *p, int a);
void func_00228BB0(struct S *p)
{
    RestAloSost__FP3ALO(p);
    SetAloSensors__FP3ALOi(p, 1);
    { struct T *t = p->t;
    t->b = 1.0f;
    t->a = 1.0f; }
}
