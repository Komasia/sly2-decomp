struct M { int a, b; };
struct B { int a; int b; char pad[0x34]; int c; };
void func_00117968(void *p, int cb, struct B *pb);
void *func_001AE238(struct M *pm, struct B *pb);
void func_00228250(void *p, void **pq)
{
    struct B b;
    struct M m;
    func_00117968(p, 0x40, &b);
    if (b.b != b.c) {
        { struct M *pm = &m; pm->a = 0x40; pm->b = 0x10; }
        *pq = func_001AE238(&m, &b);
    } else *pq = 0;
}
