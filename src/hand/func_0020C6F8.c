typedef int qword __attribute__((mode(TI)));
struct C { char pad[0xA0]; int n; };
struct B { char pad[0x58]; struct C *pc; };
struct D { char pad[0x20]; qword v; };
struct S { char pad[0x10]; int n; char pad2[0x20]; struct B *pb; char pad3[8]; qword v; char pad4[0x10]; int f60; int pad5; struct D *pd; };
qword func_0022FC48(int a, int b, qword v);
void func_0020C6F8(struct S *p, qword v)
{
    switch (p->n) {
    case 0: p->v = v; break;
    case 1: case 2:
        if (p->f60) { struct D *pd = p->pd; pd->v = func_0022FC48(0, p->pb->pc->n, v); }
        break;
    }
}
