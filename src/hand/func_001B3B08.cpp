struct E { int a[16]; };
struct S { int n; E ae[4]; int x104; int x108; };
extern "C" unsigned int func_001AE150(int n);
extern "C" int func_001B2820(E *pe);
extern "C" void func_001B3BD0(S *p, E *pe);
extern "C" int func_001B3B08(S *p)
{
    int i;
    if (p->n <= 0) return 0;
    if (func_001AE150(1) <= 0x41FC3F) { p->n = 0; return 0; }
    for (i = 0; i < p->n; i++) {
        E *pe = &p->ae[i];
        p->x104 = func_001B2820(pe);
        do { func_001B3BD0(p, pe); } while (p->x108);
        p->x104 = 0;
    }
    p->n = 0;
    return 1;
}
