struct E { int a; int b; int c; };
struct P { char pad[0x17C]; struct E ae[1]; };
int func_001B1B10(int n);
void func_001B1B18(struct P *p, int n, int a, int c)
{
    if (func_001B1B10(n) && n != 2 && n != 5) {
        struct E *pe = &p->ae[n];
        pe->a = a;
        if (c != -1)
            pe->c = c;
    }
}
