struct B { int a[3]; int c; };
struct S { int a[2]; struct B *pb; char pad[0xE4]; int f0; int f4; };
void func_001CE9B8(struct S *a, struct S *b);
void func_001CF5D0(struct S *a, struct S *b)
{
    func_001CE9B8(a, b);
    a->f0 = b->pb->c;
    a->f4 = b->f0;
}
