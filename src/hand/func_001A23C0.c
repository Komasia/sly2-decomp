struct T { int x0; };
struct S { int x0; int x4; int pad[2]; struct T *x10; char pad2[0x7C]; int x90; };
// name: SafeHouse port (NDamageStatus)
int NDamageStatus__FP5ACTOR(struct S *p)
{
    if (p->x4 != -1) return p->x10->x0 <= 0 ? 2 : 1;
    return p->x90 == 1;
}
