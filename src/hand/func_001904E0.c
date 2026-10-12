typedef int qword __attribute__((mode(TI)));
struct O { int a; int b; };
struct S { char pad[0x1900]; struct O *p; char pad2[0x1930-0x1904]; qword a; qword b; };
void func_001FAC30(int, qword);
void func_001FAC98(int, qword);
void func_001904E0(struct S *s) { func_001FAC30(s->p->b, s->a); func_001FAC98(s->p->b, s->b); }
