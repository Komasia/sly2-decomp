struct E { int pad[3]; int k; char pad2[0xB0 - 0x10]; };
struct P { char pad[0xE0]; int c; struct E *ae; };
void func_001F2AD0(struct P *, struct E *);
void func_001F6B48(struct P *p, int k)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i]; if (pe->k == k) func_001F2AD0(p, pe);
    }
}
