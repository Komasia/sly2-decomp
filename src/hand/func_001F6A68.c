typedef unsigned long ulong;
struct C { char pad[0x10]; ulong fl; };
struct E { char pad[0xC]; int fl; char pad2[0x14]; struct C *pc; };
struct A { char pad[0xB8]; int c; int pad2; struct E *ae; };
void func_001F6A68(struct A *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->fl |= 0x800;
        if (pe->pc)
            pe->pc->fl |= 1L << 50;
    }
}
