struct C { char pad[0x40]; int n; };
struct B { char pad[0x60]; struct C *pc; };
struct A { char pad[0x200]; struct B *pb; };
extern "C" int func_001FE848(struct A *p, int n)
{
    if (p->pb) {
        struct C *pc = p->pb->pc;
        bool f = false;
        if (n != -1 && pc->n == n)
            f = true;
        return f;
    }
    return 0;
}
