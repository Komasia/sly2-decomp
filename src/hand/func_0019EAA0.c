typedef int qword __attribute__((mode(TI)));
struct S { int pad[0x30/4]; qword a; qword b; };
void func_0019EAA0(struct S *s, qword a, qword b) { s->a = a; s->b = b; }
