struct E { int a; int b; int c; };
struct S { char pad[0x17C]; struct E ae[6]; };
int func_001B1B98(struct S *p, int a);
void func_001B1BF0(struct S *p)
{
    int i;
    struct E *pe;
    for (i = 0; i < 6; i++) {
        pe = &p->ae[i];
        if (pe->a != -1) {
            pe->b = func_001B1B98(p, pe->a);
            pe->a = -1;
        }
    }
}
