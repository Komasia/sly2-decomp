typedef int qword __attribute__((mode(TI)));
struct S { int a, b, c, d; qword q; };
void func_0019C300(int, int, qword, float *, int, int);
float func_0019ABB8(struct S *s) { float f[4]; func_0019C300(s->a, s->b, s->q, f, 0, 0); return f[0]; }
