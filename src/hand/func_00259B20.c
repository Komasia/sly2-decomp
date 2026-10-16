struct B { char pad[0x10]; int x10; };
struct A { char pad[0xDC]; struct B *xDC; };
struct O { char pad[0xE8]; struct A *xE8; };
int func_00259B20(struct O *p)
{
    struct A *a = p->xE8;
    struct B *b = a ? a->xDC : 0;
    return b ? b->x10 : 0;
}
