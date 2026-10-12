struct B { char pad[0x24]; int n24; char pad2[8]; int n30; int pad3; int n38; };
struct S { int n; int a; struct B *pb; };
int func_00209518(struct S *p)
{
    switch (p->n) {
    case 0: return (int)p->pb;
    case 1: return p->pb->n30;
    case 2: return p->pb->n38;
    case 3: return p->pb->n24;
    }
    return 0;
}
