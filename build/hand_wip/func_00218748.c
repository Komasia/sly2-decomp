struct E { char pad[0x10]; int f; void *p; };
struct S { char pad[8]; struct E *ae; };
void func_001FB018(void *p);
void func_00218748(struct S *p, int i)
{
    void *q;
    p->ae[i].f = 1;
    q = p->ae[i].p;
    if (q)
        func_001FB018(q);
}
