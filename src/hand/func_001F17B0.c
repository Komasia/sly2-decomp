struct E { int a; int b; int c; int d; };
struct S { char pad[0x404]; struct E ae[8]; int c; int pad2[2]; int f; };
void func_001F17B0(struct S *p, int x)
{
    if (p->c <= 0 || p->f) {
        struct E *pe = &p->ae[p->c++];
        pe->a = x; //P
        pe->b = 0; //P
        pe->c = -1; //P
        pe->d = 1; //P
    }
}
