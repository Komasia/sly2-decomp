struct E { int a; int b; int c; int d; };
struct S { char pad[0x404]; struct E ae[8]; int c; int pad2[2]; int f; };
void func_001F1768(struct S *p, int x)
{
    if (p->f) {
        struct E *pe = &p->ae[p->c++];
        pe->a = 0x2B3; pe->c = -1; pe->b = 0; pe->d = x;
    }
}
