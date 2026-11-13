struct E { int a; int b; };
struct S { char pad[0x20]; struct E *ae; };
void AddVifUnpack(int a, int b, int c, int d, int e) asm("AddVifUnpack__4VIFS3UPKiPvi");
int func_001EC688(struct S *p, int i, int x, int y)
{
    struct E *pe = &p->ae[i];
    AddVifUnpack(y, 12, pe->a, pe->b, x);
    return pe->a;
}
