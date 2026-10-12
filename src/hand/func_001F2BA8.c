typedef unsigned long ulong;
struct E { int pad[4]; ulong fl; char pad2[0xB0 - 0x18]; };
struct P { char pad[0xE0]; int c; struct E *ae; };
void func_001F2930(struct P *, struct E *);
void func_001F2BA8(struct P *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (!(pe->fl & (1L << 50))) func_001F2930(p, pe);
    }
}
