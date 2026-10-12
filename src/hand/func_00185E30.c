typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x1F30]; qword a; qword b; qword c; };
void func_00185E30(struct S *p, qword a, qword b, qword c)
{
    p->a = a;
    p->b = b;
    p->c = c;
}
