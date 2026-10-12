struct S { char pad[0x1000]; int a; int b; char p1[0xE0]; int n; float g; };
void func_001875B8(struct S *p, int a, int b);
void func_00243088(int a, int b, struct S *p);
void func_00187150(struct S *p, int a, int b)
{
    func_001875B8(p, 1, 0);
    p->a = a;
    p->b = b;
    func_00243088(a, b, p);
    p->n = 1;
    p->g = 1.0f;
}
