typedef unsigned long ulong;
struct E { int pad[4]; ulong fl; char pad2[0xB0 - 0x18]; };
struct P { char pad[0xE0]; int c; struct E *ae; };
void RemoveSoeFromOxa__FP3ALOP3SOE(struct P *, struct E *);
// name: SafeHouse port (RemoveAloSoes)
void RemoveAloSoes__FP3ALO(struct P *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (!(pe->fl & (1L << 50))) RemoveSoeFromOxa__FP3ALOP3SOE(p, pe);
    }
}
