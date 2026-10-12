typedef int qword __attribute__((mode(TI)));
struct E { int a; int b; int c; char p[0x10]; int x1c; float g; int x24; int p2; float h; };
struct S { char pad[0x1C8]; int c; struct E ae[4]; };
void func_001F50E0(struct S *p);
void func_001E7BB8(int n, qword *pa, qword *pb);
void func_001F5480(struct S *p, qword q, float g);
void func_00182780(struct S *p)
{
    int i;
    func_001F50E0(p);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        qword a, b;
        func_001E7BB8(pe->x24, &a, &b);
        func_001F5480(p, a, pe->g);
        func_001F5480(p, b, pe->g);
    }
}
