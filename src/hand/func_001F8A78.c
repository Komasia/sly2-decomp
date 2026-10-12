typedef int qword __attribute__((mode(TI)));
struct B { char pad[0xA0]; int n; };
struct A { char pad[0x24]; struct B *pb; };
qword func_0022FC48(int a, int n, qword q);
void func_001F89E0(struct A *p, int a, int b, qword q);
void func_001F8A78(struct A *p, int a, int b, qword q)
{
    func_001F89E0(p, a, b, func_0022FC48(0, p->pb->n, q));
}
